# Linux_Cam
## 这是一个Linux相机项目，具体的演示视频可以看b站链接：[BV1CozyB8EDa](https://www.bilibili.com/video/BV1CozyB8EDa/?spm_id_from=333.1387.homepage.video_card.click&vd_source=2ad95d7225f9d532c71518bc0af78efa)
其中20_i2c是陀螺仪的驱动和应用程序，用了四元数解算的方法
MyCam文件夹是Qt+Opencv的主体程序，camwindow是UI主程序，负责显示和控制，mpu_compiler和threadgetcampic分别是MPU和Cam子进程，用于获取MPU数据和Cam图像。remove_pic_dialog是删除对话框的逻辑。
