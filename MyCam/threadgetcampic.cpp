#include "threadgetcampic.h"
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>

ThreadGetCamPIc::ThreadGetCamPIc(QObject *parent)
    : QThread(parent), isRunning(false), isRecording(false), isPlaying(false)
{

}

ThreadGetCamPIc::~ThreadGetCamPIc()
{
    this->stop();
    this->wait();
}

void ThreadGetCamPIc::startCapture()
{
    QMutexLocker lock(&m_mux);
    if(!isRunning){
        isRunning =  true;
        start();
    }
}

void ThreadGetCamPIc::stop()
{
    qDebug() << "Stop Thread";
    QMutexLocker lock(&m_mux);
    isRunning = false;
    isRecording = false;
    isPlaying = false;
}

void ThreadGetCamPIc::startRecording(const std::string &filename)
{
    QMutexLocker lock(&m_mux);
    if(!isRecording){
        int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
        double fps = 24.0;
        cv::Size frameSize(800, 800);

        writer.open(filename, codec, fps, frameSize);
        if(writer.isOpened()){
            isRecording = true;
        }
    }
}

void ThreadGetCamPIc::stopRecording()
{
    QMutexLocker lock(&m_mux);
    if(isRecording){
        isRecording = false;
        if(writer.isOpened()){
            writer.release();
        }
    }
}

void ThreadGetCamPIc::ReceiveVideoName(const std::string &filename)
{
    m_filename = filename;
    QMutexLocker lock(&m_mux);
    if(!isRunning){
        isRunning =  true;
        isPlaying = true;
        start();
    }
}

void ThreadGetCamPIc::run()
{
    cv::VideoCapture stVideoCapture;
    bool bRet;
    bool FrushImg_flag;
    if(!isPlaying){
        bRet = stVideoCapture.open(0);
        FrushImg_flag = 1;
    }else{
        bRet = stVideoCapture.open(m_filename);
        FrushImg_flag = 0;
    }
    if(!bRet){
        emit sigCamcannotOpen();
        return;
    }
    stVideoCapture.set(cv::CAP_PROP_FRAME_WIDTH, 800);
    stVideoCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 800);
    qDebug() << stVideoCapture.get(cv::CAP_PROP_FPS);
    // stVideoCapture.set(cv::CAP_PROP_FPS, 24);

    cv::Mat matTemp;
    QImage imgTemp;
    stVideoCapture >> matTemp;

    while(1){
        {
            QMutexLocker lock(&m_mux);
            if(!isRunning) break;
        }

        {
            QMutexLocker lock(&m_mux);
            if(isRecording && writer.isOpened()){
                writer.write(matTemp);
            }
        }

        stVideoCapture >> matTemp;
        if(matTemp.empty()){
            emit sigVideoisEnd();
            msleep(10);
            qDebug() << "matTemp is empty";
            continue;
        }
        imgTemp = QImage(matTemp.data, matTemp.cols, matTemp.rows, matTemp.step, QImage::Format_BGR888).copy();
        emit sigSendCurImg(imgTemp);

        {
            QMutexLocker lock(&m_mux);
            if(isRecording && writer.isOpened()){
                writer.write(matTemp);
            }
        }
        msleep(10);

        {
            QMutexLocker lock(&m_mux);
            if(isRecording && writer.isOpened()){
                writer.write(matTemp);
            }
        }
        msleep(10);
    }

    if(FrushImg_flag){
        emit ShowAlbumPic();
    }
}


