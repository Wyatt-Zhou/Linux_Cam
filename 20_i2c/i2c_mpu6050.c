/***************************************************************
Copyright © ALIENTEK Co., Ltd. 1998-2029. All rights reserved.
文件名  	: mpu6050.c
作者     	: 正点原子Linux团队
版本     	: V1.0
描述    	: mpu6050驱动程序
其他    	: 无
论坛    	: www.openedv.com
日志    	: 初版V1.0 2021/03/19 正点原子Linux团队创建
***************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/device.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
//#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "i2c_mpu6050.h"

/*字符设备内容*/
#define DEV_CNT     1
#define DEV_NAME    "I2C1_mpu6050"

struct mpu6050_dev {
    struct i2c_client *client;  	/* i2c 设备 		*/
    dev_t devid;            		/* 设备号    	 	*/
    struct cdev cdev;       		/* cdev     		*/
    struct class *class;    		/* 类      			*/
    struct device *device;  		/* 设备    			*/
    struct device_node  *nd; 	/* 设备节点 			*/
};
/*
 * @description	:	从mpu6050读取多个寄存器数据
 * @param – dev	: 	mpu6050设备
 * @param – reg	:  	要读取的寄存器首地址
 * @param – val	:  	读取到的数据
 * @param – len	:  	要读取的数据长度
 * @return      	: 	操作结果
 */
static int mpu6050_read_regs(struct mpu6050_dev *dev, u8 reg, void *val, int len)
{
    int ret;
    struct i2c_msg msg[2];
    struct i2c_client *client = (struct i2c_client *)dev->client;

    /* msg[0]为发送要读取的首地址 */
    msg[0].addr = client->addr;      	    /* mpu6050地址 	*/
    msg[0].flags = 0;                   	/* 标记为发送数据 	*/
    msg[0].buf = &reg;                		/* 读取的首地址 		*/
    msg[0].len = 1;                     	/* reg长度			*/

    /* msg[1]读取数据 */
    msg[1].addr = client->addr;         	/* mpu6050地址 	*/
    msg[1].flags = I2C_M_RD;            	/* 标记为读取数据	*/
    msg[1].buf = val;                   	/* 读取数据缓冲区 	*/
    msg[1].len = len;                   	/* 要读取的数据长度	*/

    ret = i2c_transfer(client->adapter, msg, 2);
    if(ret == 2) {
        ret = 0;
    } else {
        printk("i2c rd failed=%d reg=%06x len=%d\n",ret, reg, len);
        ret = -EREMOTEIO;
    }
    return ret;
}

/*
 * @description:	向mpu6050多个寄存器写入数据
 * @param - dev: 	mpu6050设备
 * @param - reg: 	要写入的寄存器首地址
 * @param - val: 	要写入的数据缓冲区
 * @param - len: 	要写入的数据长度
 * @return    :   	操作结果
 */
static s32 mpu6050_write_regs(struct mpu6050_dev *dev, u8 reg, u8 *buf, u8 len)
{
    u8 b[256];
    struct i2c_msg msg;
    struct i2c_client *client = (struct i2c_client *)dev->client;
    
    b[0] = reg;                 	/* 寄存器首地址 						*/
    memcpy(&b[1],buf,len);      	/* 将要写入的数据拷贝到数组b里面 	*/
        
    msg.addr = client->addr;    	/* mpu6050地址 					*/
    msg.flags = 0;              	/* 标记为写数据 						*/

    msg.buf = b;                	/* 要写入的数据缓冲区 				*/
    msg.len = len + 1;          	/* 要写入的数据长度 					*/

    return i2c_transfer(client->adapter, &msg, 1);
}

/*
 * @description:	读取mpu6050_dev指定寄存器值，读取一个寄存器
 * @param - dev: 	mpu6050_dev设备
 * @param - reg: 	要读取的寄存器
 * @return    :   	读取到的寄存器值
 */
/*
static unsigned char mpu6050_read_reg(struct mpu6050_dev *dev, u8 reg)
{
    u8 data = 0;

    mpu6050_read_regs(dev, reg, &data, 1);
    return data;
}*/

/*
 * @description: 	向mpu6050指定寄存器写入指定的值，写一个寄存器
 * @param - dev: 	mpu6050设备
 * @param - reg: 	要写的寄存器
 * @param - data:	要写入的值
 * @return   :    	无
 */
static void mpu6050_write_reg(struct mpu6050_dev *dev, u8 reg, u8 data)
{
    u8 buf = 0;
    buf = data;
    mpu6050_write_regs(dev, reg, &buf, 1);
}

/*
 * @description  	: 打开设备
 * @param – inode	: 传递给驱动的inode
 * @param - filp 	: 设备文件，file结构体有个叫做private_data的成员变量
 *                     一般在open的时候将private_data指向设备结构体。
 * @return       	: 0 成功;其他 失败
 */
static int mpu6050_open(struct inode *inode, struct file *filp)
{
    /* 从file结构体获取cdev指针，再根据cdev获取mpu6050_dev首地址 */
    struct cdev *cdev = filp->f_path.dentry->d_inode->i_cdev;
    struct mpu6050_dev *mpu6050dev = container_of(cdev, struct mpu6050_dev, cdev);
    int ret;
    char MPU_NAME;

    /*配置mpu6050*/
    mpu6050_write_reg(mpu6050dev, PWR_MGMT_1, 0x80);
    mdelay(100);
    mpu6050_write_reg(mpu6050dev, PWR_MGMT_1, 0x00);
    mpu6050_write_reg(mpu6050dev, PWR_MGMT_1, 0x01);
    mpu6050_write_reg(mpu6050dev, PWR_MGMT_2, 0x00);
    mpu6050_write_reg(mpu6050dev, GYRO_CONFIG, 0x18);
    mpu6050_write_reg(mpu6050dev, ACCEL_CONFIG, 0x18);
    mpu6050_write_reg(mpu6050dev, SMPLRT_DIV, 0x07);
    mpu6050_write_reg(mpu6050dev, CONFIG, 0x06);
    ret = mpu6050_read_regs(mpu6050dev, WHO_AM_I, &MPU_NAME, 1);
    if (ret == 0)
    {
        printk("mpu read address success\r\n");
        printk("address is : %c\r\n", MPU_NAME);
    }
    else
    {
        printk("mpu read address fail!\r\n");
    }

    return 0;
}

/*
 * @description 	: 从设备读取数据 
 * @param - filp 	: 要打开的设备文件(文件描述符)
 * @param - buf 	: 返回给用户空间的数据缓冲区
 * @param - cnt  	: 要读取的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return        	: 读取的字节数，如果为负值，表示读取失败
 */
static ssize_t mpu6050_read(struct file *filp, char __user *buf, size_t cnt, loff_t *off)
{
    char data_H;
    char data_L;
    int err = 0;
    short mpu6050_result[6];

    struct cdev *cdev = filp->f_path.dentry->d_inode->i_cdev;
    struct mpu6050_dev *mpu6050dev = container_of(cdev, struct mpu6050_dev, cdev);
    
    mpu6050_read_regs(mpu6050dev, ACCEL_XOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, ACCEL_XOUT_L, &data_L, 1);
    mpu6050_result[0] = data_H << 8;
    mpu6050_result[0] += data_L;

    mpu6050_read_regs(mpu6050dev, ACCEL_YOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, ACCEL_YOUT_L, &data_L, 1);
    mpu6050_result[1] = data_H << 8;
    mpu6050_result[1] += data_L;

    mpu6050_read_regs(mpu6050dev, ACCEL_ZOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, ACCEL_ZOUT_L, &data_L, 1);
    mpu6050_result[2] = data_H << 8;
    mpu6050_result[2] += data_L;

    mpu6050_read_regs(mpu6050dev, GYRO_XOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, GYRO_XOUT_L, &data_L, 1);
    mpu6050_result[3] = data_H << 8;
    mpu6050_result[3] += data_L;

    mpu6050_read_regs(mpu6050dev, GYRO_YOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, GYRO_YOUT_L, &data_L, 1);
    mpu6050_result[4] = data_H << 8;
    mpu6050_result[4] += data_L;

    mpu6050_read_regs(mpu6050dev, GYRO_ZOUT_H, &data_H, 1);
    mpu6050_read_regs(mpu6050dev, GYRO_ZOUT_L, &data_L, 1);
    mpu6050_result[5] = data_H << 8;
    mpu6050_result[5] += data_L;
    
    err = copy_to_user(buf, mpu6050_result, cnt);

    if(err != 0)
    {
        printk("copy to user error!");
        return -1;
    }
    return 0;
}

/*
 * @description 	: 关闭/释放设备
 * @param - filp 	: 要关闭的设备文件(文件描述符)
 * @return        	: 0 成功;其他 失败
 */
static int mpu6050_release(struct inode *inode, struct file *filp)
{
    return 0;
}

/* MPU6050操作函数 */
static const struct file_operations mpu6050_ops = {
    .owner = THIS_MODULE,
    .open = mpu6050_open,
    .read = mpu6050_read,
    .release = mpu6050_release,
};

 /*
  * @description 	: i2c驱动的probe函数，当驱动与
  *                    设备匹配以后此函数就会执行
  * @param – client	: i2c设备
  * @param - id      	: i2c设备ID
  * @return          	: 0，成功;其他负值,失败
  */
static int mpu6050_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret;
    struct mpu6050_dev *mpu6050dev;
    
    
    mpu6050dev = devm_kzalloc(&client->dev, sizeof(*mpu6050dev), GFP_KERNEL);
    if(!mpu6050dev)
         return -ENOMEM;
         
     /* 注册字符设备驱动 */
     /* 1、创建设备号 */
     ret = alloc_chrdev_region(&mpu6050dev->devid, 0, DEV_CNT, DEV_NAME);
     if(ret < 0) {
         pr_err("%s Couldn't alloc_chrdev_region, ret=%d\r\n", DEV_NAME, ret);
         return -ENOMEM;
     }

     /* 2、初始化cdev */
     mpu6050dev->cdev.owner = THIS_MODULE;
     cdev_init(&mpu6050dev->cdev, &mpu6050_ops);
     
     /* 3、添加一个cdev */
     ret = cdev_add(&mpu6050dev->cdev, mpu6050dev->devid, DEV_CNT);
    if(ret < 0) {
        goto del_unregister;
    }
    
    /* 4、创建类 */
    mpu6050dev->class = class_create(THIS_MODULE, DEV_NAME);
    if (IS_ERR(mpu6050dev->class)) {
        goto del_cdev;
    }

    /* 5、创建设备 */
    mpu6050dev->device = device_create(mpu6050dev->class, NULL, mpu6050dev->devid, NULL, DEV_NAME);
    if (IS_ERR(mpu6050dev->device)) {
        goto destroy_class;
    }
    mpu6050dev->client = client;
    /* 保存mpu6050dev结构体 */
    i2c_set_clientdata(client,mpu6050dev);

    return 0;
destroy_class:
    device_destroy(mpu6050dev->class, mpu6050dev->devid);
del_cdev:
    cdev_del(&mpu6050dev->cdev);
del_unregister:
    unregister_chrdev_region(mpu6050dev->devid, DEV_CNT);
    return -EIO;
}

/*
 * @description  : i2c驱动的remove函数，移除i2c驱动的时候此函数会执行
 * @param - client  	: i2c设备
 * @return          	: 0，成功;其他负值,失败
 */
static int mpu6050_remove(struct i2c_client *client)
{
    struct mpu6050_dev *mpu6050dev = i2c_get_clientdata(client);
    /* 注销字符设备驱动 */
    /* 1、删除cdev */
    cdev_del(&mpu6050dev->cdev);
    /* 2、注销设备号 */
    unregister_chrdev_region(mpu6050dev->devid, DEV_CNT); 
    /* 3、注销设备 */
    device_destroy(mpu6050dev->class, mpu6050dev->devid);
    /* 4、注销类 */
    class_destroy(mpu6050dev->class); 
    return 0;
}

/* 传统匹配方式ID列表 */
static const struct i2c_device_id mpu6050_id[] = {
    {"zwy,mpu6050", 0},  
    {}
};

/* 设备树匹配列表 */
static const struct of_device_id mpu6050_of_match[] = {
    { .compatible = "zwy,mpu6050" },
    { /* Sentinel */ }
};

/* i2c驱动结构体 */    
static struct i2c_driver mpu6050_driver = {
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
    .driver = {
            .owner = THIS_MODULE,
            .name = "mpu6050",
            .of_match_table = mpu6050_of_match, 
           },
    .id_table = mpu6050_id,
};
           
/*
 * @description 	: 驱动入口函数
 * @param       	: 无
 * @return      	: 无
 */
static int __init mpu6050_init(void)
{
    int ret = 0;

    ret = i2c_add_driver(&mpu6050_driver);
    return ret;
}

/*
 * @description 	: 驱动出口函数
 * @param       	: 无
 * @return      	: 无
 */
static void __exit mpu6050_exit(void)
{
    i2c_del_driver(&mpu6050_driver);
}

/* module_i2c_driver(mpu6050_driver) */

module_init(mpu6050_init);
module_exit(mpu6050_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZWY");
MODULE_INFO(intree, "Y");
