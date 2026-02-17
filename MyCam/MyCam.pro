QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# /*************PC*************/
#INCLUDEPATH += /opt/opencv4-pc/include/opencv4
#INCLUDEPATH += /opt/opencv4-pc/include/opencv4/opencv2
#INCLUDEPATH += /home/zwy/ffmpeg-4.4/build/FFmpeg/include/

#LIBS+=-L/opt/opencv4-pc/lib -lopencv_world
#LIBS+=-L/home/zwy/ffmpeg-4.4/build/FFmpeg/lib -lavcodec -lavformat -lavutil -lavresample -lswscale


# /*************Development Board*************/
INCLUDEPATH += /opt/atk-dlrk356x-toolchain/aarch64-buildroot-linux-gnu/sysroot/usr/include/opencv4/opencv2
INCLUDEPATH += /opt/atk-dlrk356x-toolchain/aarch64-buildroot-linux-gnu/sysroot/usr/include/opencv4

LIBS+=-L/opt/atk-dlrk356x-toolchain/aarch64-buildroot-linux-gnu/sysroot/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    camwindow.cpp \
    mpu_compiler.cpp \
    remove_pic_dialog.cpp \
    threadgetcampic.cpp

HEADERS += \
    camwindow.h \
    mpu_compiler.h \
    remove_pic_dialog.h \
    threadgetcampic.h

FORMS += \
    camwindow.ui \
    remove_pic_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
