#ifndef THREADGETCAMPIC_H
#define THREADGETCAMPIC_H

#include <opencv2/opencv.hpp>
#include <QThread>
#include <QMutex>

class ThreadGetCamPIc : public QThread
{
    Q_OBJECT

public:
    ThreadGetCamPIc(QObject *parent);
    ~ThreadGetCamPIc();

    void startCapture();
    void stop();

    void startRecording(const std::string &filename);
    void stopRecording();
    void ReceiveVideoName(const std::string &filename);

    void run();

signals:
    void sigSendCurImg(const QImage& img);
    void sigCamcannotOpen();
    void sigVideoisEnd();

    void ShowAlbumPic();

private:
    bool isRunning;
    bool isRecording;
    bool isPlaying;
    cv::VideoWriter writer;
    QMutex m_mux;
    std::string m_filename;
};

#endif // THREADGETCAMPIC_H
