#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include "math.h"

#define PI 3.1415926535f
#define RtA 57.2957795f
#define AtR 0.0174532925

const float Kp = 2.0f;
const float Ki = 0.005f;

typedef struct 
{
    float q0, q1, q2, q3;
} Quaternion;
 
Quaternion q = {1.0f, 0.0f, 0.0f, 0.0f};  // 初始化四元数

void NormalizeAccel(float *ax, float *ay, float *az)
{
    float norm;
    norm = sqrt(*ax * *ax + *ay * *ay + *az * *az);

    if(norm == 0){
        *ax = 0.0f;
        *ay = 0.0f;
        *az = 0.0f;
        return;
    }
    *ax /= norm;
    *ay /= norm;
    *az /= norm;
}

void ComputeError(float ax, float ay, float az, float *error_x, float *error_y, float *error_z)
{
    // printf("After ComputeError : ax = %f, ay = %f, az = %f\r\n", ax, ay, az);
    // printf("After ComputeError : q.q0 = %f, q.q1 = %f, q.q2 = %f, q.q3 = %f\r\n", q.q0, q.q1, q.q2, q.q3);
    float gravity_x = q.q1 * q.q3 - q.q0 * q.q2;
    float gravity_y = q.q0 * q.q1 + q.q2 * q.q3;
    float gravity_z = q.q0 * q.q0 + q.q3 * q.q3 - 0.5f;

    // printf("After ComputeError : gravity_x = %f, gravity_y = %f, gravity_z = %f\r\n", gravity_x, gravity_y, gravity_z);

    *error_x = (ay * gravity_z - az * gravity_y);
    *error_y = (az * gravity_x - ax * gravity_z);
    *error_z = (ax * gravity_y - ay * gravity_x);
    // printf("After ComputeError : error_x = %f, error_y = %f, error_z = %f\r\n", *error_x, *error_y, *error_z);
}

void UpdateQuaternion(float gx, float gy, float gz, float error_x, float error_y, float error_z, float dt)
{
    float integ_x = 0.0f, integ_y = 0.0f, integ_z = 0.0f;
    // 积分误差
    integ_x += Ki * error_x;
    integ_y += Ki * error_y;
    integ_z += Ki * error_z;
    // printf("Update Quaternion : error_x = %f, error_y = %f, error_z = %f\r\n", error_x, error_y, error_z);
    // printf("Update Quaternion : integ_x = %f, integ_y = %f, integ_z = %f\r\n", integ_x, integ_y, integ_z);

    // 应用比例+积分反馈到陀螺仪
    gx += Kp * error_x + integ_x;
    gy += Kp * error_y + integ_y;
    gz += Kp * error_z + integ_z;
    // printf("Update Quaternion : gx = %f, gy = %f, gz = %f\r\n", gx, gy, gz);

    float q0_dot = -q.q1 * gx - q.q2 * gy - q.q3 * gz;
    float q1_dot = q.q0 * gx - q.q3 * gy + q.q2 * gz;
    float q2_dot = q.q3 * gx + q.q0 * gy - q.q1 * gz;
    float q3_dot = -q.q2 * gx + q.q1 * gy + q.q0 * gz;
    // printf("Update Quaternion : q0_dot = %f, q1_dot = %f, q2_dot = %f, q3_dot = %f\r\n", q0_dot, q1_dot, q2_dot, q3_dot);

    q.q0 += q0_dot * 0.5f * dt;
    q.q1 += q1_dot * 0.5f * dt;
    q.q2 += q2_dot * 0.5f * dt;
    q.q3 += q3_dot * 0.5f * dt;
    // printf("Update Quaternion q_dot*0.5*dt : q.q0= %f, q.q1 = %f, q.q2 = %f, q.q3 = %f\r\n", q.q0, q.q1, q.q2, q.q3);

    // Normalization, avoid the values from getting larger
    float norm = sqrt(q.q0 * q.q0 + q.q1 * q.q1 + q.q2 * q.q2 + q.q3 * q.q3);
    q.q0 /= norm;
    q.q1 /= norm;
    q.q2 /= norm;
    q.q3 /= norm;
    // printf("Update Quaternion normalization : q.q0= %f, q.q1 = %f, q.q2 = %f, q.q3 = %f\r\n", q.q0, q.q1, q.q2, q.q3);
}

void ComputeEulerAngles(float *pitch, float *roll, float *yaw)
{
    *roll = atan2(2 * (q.q2 * q.q3 + q.q0 * q.q1), 1.0f - 2.0f * (q.q1 * q.q1 + q.q2 * q.q2));
    *pitch = asin(2 * (q.q0 * q.q2 - q.q1 * q.q3));
    *yaw = atan2(2 * (q.q1 * q.q2 + q.q0 * q.q3), 1.0f - 2.0f * (q.q2 * q.q2 + q.q3 * q.q3));

    *roll *= RtA;   //rad 2 angle
    *pitch *= RtA;
    *yaw *= RtA;
}

/*
 * @description 	: main主程序
 * @param - argc 	: argv数组元素个数
 * @param - argv 	: 具体参数
 * @return        	: 0 成功;其他 失败
 */
int main(int argc, char *argv[])
{
    int8_t fd;
    static int count = 0;
    float ax, ay, az, gx, gy, gz;
    float error_x, error_y, error_z;
    float pitch, roll, yaw;
    char *filename;
    short databuf[6];

    int ret = 0;
    if (argc != 2) {
        printf("Error Usage!\r\n");
        return -1;
    }

    filename = argv[1];
    fd = open(filename, O_RDWR);
    if(fd < 0) {
        printf("can't open file %s\r\n", filename);
        return -1;
    }

    /*for(i=0; i<100; i++){
        ret = read(fd, databuf, sizeof(databuf));
        if(ret == 0) {     //数据读取成功
            printf("AX = %f, AY = %f, AZ = %f\r\n", (float)databuf[0], (float)databuf[1], (float)databuf[2]);
            printf("GX = %f, GY = %f, GZ = %f\r\n", (float)databuf[3], (float)databuf[4], (float)databuf[5]);
        }
        usleep(10000);
    }

    gx = 0.0f;
    gy = 0.0f;
    gz = 0.0f;
    for(i=0; i<2000; i++){
        ret = read(fd, databuf, sizeof(databuf));
        if(ret == 0) {     //数据读取成功
            // ax += (float)databuf[0];
            // ay += (float)databuf[1];
            // az += (float)databuf[2];
            // printf("AX = %f, AY = %f, AZ = %f\r\n", (float)databuf[0], (float)databuf[1], (float)databuf[2]);
            // printf("AX total = %f, AY total = %f, AZ total = %f\r\n", ax, ay, az);
            gx += (float)databuf[3];
            gy += (float)databuf[4];
            gz += (float)databuf[5];
            printf("GX = %f, GY = %f, GZ = %f\r\n", (float)databuf[3], (float)databuf[4], (float)databuf[5]);
            printf("GX total = %f, GY total = %f, GZ total = %f\r\n", gx, gy, gz);
        }
        usleep(10000);
    }
    gx = gx / 2000;
    gy = gy / 2000;
    gz = gz / 2000;
    printf("GX total = %f, GY total = %f, GZ total = %f\r\n", gx, gy, gz);*/
    


    while (1) {
        ret = read(fd, databuf, sizeof(databuf));
        if(ret == 0) {     //数据读取成功
            // printf("AX = %f, AY = %f, AZ = %f\r\n", (float)databuf[0], (float)databuf[1], (float)databuf[2]);
            // printf("GX = %f, GY = %f, GZ = %f\r\n", (float)databuf[3], (float)databuf[4], (float)databuf[5]);
            ax = ((float)databuf[0] - 73) / 2048;
            ay = ((float)databuf[1] + 29.78) / 2048;
            az = ((float)databuf[2] + 64) / 2048;

            gx = ((float)databuf[3] + 35.5) * AtR / 16.4;
            gy = ((float)databuf[4] + 18) * AtR / 16.4;
            gz = ((float)databuf[5] - 0.75) * AtR / 16.4;

            // printf("first step: AX = %f, AY = %f, AZ = %f\r\n", ax, ay, az);
            // printf("first step: GX = %f, GY = %f, GZ = %f\r\n", gx, gy, gz);

            NormalizeAccel(&ax, &ay, &az);
            // printf("second step: AX = %f, AY = %f, AZ = %f\r\n", ax, ay, az);

            ComputeError(ax, ay, az, &error_x, &error_y, &error_z);
            // printf("third step: error_x = %f, error_y = %f, error_z = %f\r\n", error_x, error_y, error_z);
            // printf("third step: AX = %f, AY = %f, AZ = %f\r\n", ax, ay, az);
            UpdateQuaternion(gx, gy, gz, error_x, error_y, error_z, 0.01f);
            
            if(++count >= 20) {
                count = 0;
                ComputeEulerAngles(&pitch, &roll, &yaw);

                printf("pitch = %f, roll = %f, yaw = %f\r\n", pitch, roll, yaw);
            }
            
        }
        // usleep(1000000);
        usleep(10000); 	//100ms
    }

    close(fd);  			/* 关闭文件 */  
    return 0;
}

