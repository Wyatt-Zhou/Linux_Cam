#include "camwindow.h"
#include "ui_camwindow.h"
#include "remove_pic_dialog.h"
#include "mpu_compiler.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QThread>
#include <QDateTime>
#include <QImageWriter>

CamWindow::CamWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CamWindow)
    , m_stThreadGetCamPic(this)
{
    ui->setupUi(this);
    ui->RecordBtn->setStyleSheet(
        "QPushButton { border-image: url(:/icon/Record.png) }"
        "QPushButton:checked { border-image: url(:/icon/Recording.png); }"
        );

    ui->TakePhoto->setStyleSheet(
        "QPushButton { border-image: url(:/icon/take_photo.png) }"
        "QPushButton:pressed,QPushButton::checked { border-image: url(:/icon/take_photo_pressed.png); }"
        );

    ui->AlbumBtn->show();
    ui->TakePhoto->show();
    ui->RecordBtn->show();
    ui->ReturnBtn->hide();
    ui->NextPicBtn->hide();
    ui->PrePicBtn->hide();
    ui->DeleteBtn->hide();
    ui->PlayBtn->hide();

    m_push_takephoto_flag = 0;
    m_static_pic_rotate_flag = 0;
    connect(ui->ReturnBtn, &QPushButton::clicked, this, &CamWindow::Return2Cam);
    connect(ui->PrePicBtn, &QPushButton::clicked, this, &CamWindow::ShowPreviousPic);
    connect(ui->NextPicBtn, &QPushButton::clicked, this, &CamWindow::ShowNextPic);

    connect(ui->AlbumBtn, &QPushButton::clicked, this, &CamWindow::StopShowPic);
    connect(&m_stThreadGetCamPic, &ThreadGetCamPIc::ShowAlbumPic, this, &CamWindow::OpenAlbum);

    connect(&m_stThreadGetCamPic, &ThreadGetCamPIc::sigSendCurImg, this, &CamWindow::onFreshCurImg);
    connect(&m_stThreadGetCamPic, &ThreadGetCamPIc::sigCamcannotOpen, this, &CamWindow::CamOpenError);
    connect(&m_stThreadGetCamPic, &ThreadGetCamPIc::sigVideoisEnd, this, &CamWindow::VideoPlayEnd);

    connect(ui->TakePhoto, &QPushButton::clicked, this, &CamWindow::SavePic2Album);
    connect(ui->DeleteBtn, &QPushButton::clicked, this, &CamWindow::DeletePic);

    connect(ui->RecordBtn, &QPushButton::toggled, this, &CamWindow::RecordVideo);
    connect(ui->PlayBtn, &QPushButton::clicked, this, &CamWindow::PlayRecVideo);

    QString currentPath = QCoreApplication::applicationDirPath();
    m_album_path = currentPath.append("/album");

    QDir album_dir(m_album_path);
    if(!album_dir.exists()){
        album_dir.mkdir(m_album_path);
    }
    m_stThreadGetCamPic.startCapture();

    //start MPU6050
    compilerController = new MPU_CompilerController;
    connect(compilerController, &MPU_CompilerController::threadFinished, this, [ = ](){
        delete compilerController;
        compilerController = NULL;
    });

    QStringList arguments;
    arguments << "-o0" << "/lib/modules/4.19.232/mpu6050App" << "/dev/I2C1_mpu6050";
    compilerController->sendOperateSignal(arguments);
    //MPU6050
    connect(compilerController, &MPU_CompilerController::sigSendRotate, this, &CamWindow::RotateLabel);
}

CamWindow::~CamWindow()
{
    delete ui;
}

void CamWindow::OpenAlbum()
{
    ui->AlbumBtn->hide();
    ui->TakePhoto->hide();
    ui->RecordBtn->hide();
    ui->ReturnBtn->show();

    QDir album_dir(m_album_path);

    QFileInfoList list = album_dir.entryInfoList(QDir::Filters(QDir::Files), QDir::SortFlags(QDir::Time));
    if(list.empty()){
        ui->label->setText(tr("NO Photos, please take photos first"));
        return;
    }

    ui->NextPicBtn->show();
    ui->PrePicBtn->show();
    ui->DeleteBtn->show();
    m_all_pic_path.clear();     //after push album button, refresh the list
    for(int i=0; i<list.size(); i++){
        QFileInfo fileInfo = list.at(i);
        const QString& suffix = fileInfo.completeSuffix();
        if(suffix != "png" && suffix != "jpeg" && suffix != "jpg" && suffix != "mp4"){
            continue;
        }
        QString file_path = fileInfo.filePath();
        qDebug() << "file_path is " << file_path;
        m_all_pic_path.append(file_path);
    }
    m_pic_count = m_all_pic_path.size();
    qDebug("the pic count is:%d", m_pic_count);
    /*for(int i=0; i<m_pic_count; i++){
    qDebug() << "file Path:" << m_all_pic_path.at(i);
    }*/

    m_pic_sequence = 0;
    m_strFileName = m_all_pic_path.at(m_pic_sequence);
    cv::Mat OpenImg;
    if(m_strFileName.right(3) == "mp4"){
        m_static_pic_rotate_flag = 0;
        //get the first frame and show play button
        qDebug() << "file Name:" << m_strFileName;
        cv::VideoCapture cap;
        cap.open(m_strFileName.toStdString());
        cap.read(OpenImg);
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
        cap.release();
        ui->PlayBtn->show();
    }else{
        m_static_pic_rotate_flag = 1;
        qDebug() << "file Name:" << m_strFileName;
        OpenImg = cv::imread(m_strFileName.toLocal8Bit().data());
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
    }

    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

    m_pix2Show = QPixmap::fromImage(m_img2Show);
    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);


}

void CamWindow::Return2Cam()
{
    m_stThreadGetCamPic.startCapture();
    ui->AlbumBtn->show();
    ui->TakePhoto->show();
    ui->RecordBtn->show();
    ui->ReturnBtn->hide();
    ui->NextPicBtn->hide();
    ui->PrePicBtn->hide();
    ui->DeleteBtn->hide();
    ui->PlayBtn->hide();
    ui->label->setText("camera");
    m_static_pic_rotate_flag = 0;
}

void CamWindow::ShowPreviousPic()
{
    m_pic_sequence = m_pic_sequence-1;
    if(m_pic_sequence < 0){
        m_pic_sequence = m_pic_count - 1;
    }
    m_strFileName = m_all_pic_path.at(m_pic_sequence);
    cv::Mat OpenImg;
    m_static_pic_rotate_flag = 1;
    if(m_strFileName.right(3) == "mp4"){
        ui->PlayBtn->show();
        cv::VideoCapture cap;
        cap.open(m_strFileName.toStdString());
        cap.read(OpenImg);
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
        cap.release();
    }else{
        ui->PlayBtn->hide();
        OpenImg = cv::imread(m_strFileName.toLocal8Bit().data());
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
    }
    //qDebug() << "Previous Pic Path:" << m_strFileName;
    qDebug("After Press Previous Button, m_pic_sequence is %d", m_pic_sequence);

    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

    m_pix2Show = QPixmap::fromImage(m_img2Show);
    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);
}

void CamWindow::ShowNextPic()
{
    m_pic_sequence = m_pic_sequence+1;
    if(m_pic_sequence == m_pic_count){
        m_pic_sequence = 0;
    }
    m_strFileName = m_all_pic_path.at(m_pic_sequence);
    cv::Mat OpenImg;
    m_static_pic_rotate_flag = 1;
    if(m_strFileName.right(3) == "mp4"){
        ui->PlayBtn->show();
        cv::VideoCapture cap;
        cap.open(m_strFileName.toStdString());
        cap.read(OpenImg);
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
        cap.release();
    }else{
        ui->PlayBtn->hide();
        OpenImg = cv::imread(m_strFileName.toLocal8Bit().data());
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
    }
    //qDebug() << "Next Pic Path:" << m_strFileName;
    qDebug("After Press Next Button, m_pic_sequence is %d", m_pic_sequence);

    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

    m_pix2Show = QPixmap::fromImage(m_img2Show);
    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);
}

void CamWindow::onFreshCurImg(const QImage &img)
{
    m_imgSrc = img.copy();
    if(m_push_takephoto_flag){
        m_push_takephoto_flag = 0;
        m_dateTime = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
        m_picname = "image-" + m_dateTime + ".jpg";

        m_picpath = m_album_path + "/" + m_picname;
        QImageWriter writer(m_picpath);
        writer.setFormat("JPEG");
        writer.write(m_imgSrc);
    }

    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

    m_pix2Show = QPixmap::fromImage(m_img2Show);

    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);
}

void CamWindow::CamOpenError()
{
    ui->label->setText(tr("Camera open failed!!"));
}

void CamWindow::SavePic2Album()
{
    m_push_takephoto_flag = 1;
    qDebug() << "Press Take Photo";
}

void CamWindow::StopShowPic()
{
    m_stThreadGetCamPic.stop();
    qDebug() << "Stop CamWindow";
}

void CamWindow::DeletePic()
{
    Remove_Pic_Dialog remove_pic_dialog;
    auto res = remove_pic_dialog.exec();
    if(res != QDialog::Accepted){
        return;
    }
    m_strFileName = m_all_pic_path.at(m_pic_sequence);
    //qDebug() << "m_strFileName is " << m_strFileName;
    m_all_pic_path.removeOne(m_strFileName);
    m_pic_count = m_all_pic_path.size();
    QFile pic(m_strFileName);
    pic.remove();

    if(m_pic_count == 0){
        ui->label->setText(tr("NO Photos, please take photos first"));
        ui->NextPicBtn->hide();
        ui->PrePicBtn->hide();
        ui->DeleteBtn->hide();
        ui->PlayBtn->hide();
        return;
    }

    if(m_pic_sequence == m_pic_count){
        m_pic_sequence = m_pic_count - 1;
    }

    m_strFileName = m_all_pic_path.at(m_pic_sequence);

    cv::Mat OpenImg;
    m_static_pic_rotate_flag = 1;
    if(m_strFileName.right(3) == "mp4"){
        m_static_pic_rotate_flag = 0;
        ui->PlayBtn->show();
        cv::VideoCapture cap;
        cap.open(m_strFileName.toStdString());
        cap.read(OpenImg);
        m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
        cap.release();
    }else{
        ui->PlayBtn->hide();
        OpenImg = cv::imread(m_strFileName.toLocal8Bit().data());
    }

    m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pix2Show = QPixmap::fromImage(m_img2Show);
    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);
}

void CamWindow::RecordVideo()
{
    if(ui->RecordBtn->isChecked()){
        qDebug() << "video is recording";

        m_dateTime = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
        m_picname = "video-" + m_dateTime + ".mp4";
        m_picpath = m_album_path + "/" + m_picname;
        if(!m_picpath.isEmpty()){
            m_stThreadGetCamPic.startRecording(m_picpath.toStdString());
            ui->TakePhoto->setEnabled(false);
            ui->AlbumBtn->setEnabled(false);
        }
    }

    if(!(ui->RecordBtn->isChecked()))
    {
        m_stThreadGetCamPic.stopRecording();
        ui->TakePhoto->setEnabled(true);
        ui->AlbumBtn->setEnabled(true);
        qDebug() << "video is stop recording";
    }
}

void CamWindow::PlayRecVideo()
{
    ui->PlayBtn->hide();
    ui->DeleteBtn->hide();
    ui->ReturnBtn->hide();
    ui->NextPicBtn->hide();
    ui->PrePicBtn->hide();
    m_static_pic_rotate_flag = 0;
    m_stThreadGetCamPic.ReceiveVideoName(m_strFileName.toStdString());
}

void CamWindow::VideoPlayEnd()
{
    m_stThreadGetCamPic.stop();
    ui->DeleteBtn->show();
    ui->ReturnBtn->show();
    ui->NextPicBtn->show();
    ui->PrePicBtn->show();

    cv::Mat OpenImg;
    //get the first frame and show play button
    qDebug() << "file Name:" << m_strFileName;
    cv::VideoCapture cap;
    cap.open(m_strFileName.toStdString());
    cap.read(OpenImg);
    m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
    cap.release();
    ui->PlayBtn->show();

    m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pix2Show = QPixmap::fromImage(m_img2Show);
    if(m_rotate_flag){
        QTransform transform;
        transform.rotate(270);
        m_pix2Show = m_pix2Show.transformed(transform);
    }
    ui->label->setPixmap(m_pix2Show);
    m_static_pic_rotate_flag = 1;
}

void CamWindow::RotateLabel(const bool rotate_flag)
{
    m_rotate_flag = rotate_flag;
    qDebug() << "rotate_flag is " << rotate_flag;
    if(m_static_pic_rotate_flag == 1){
        // cv::Mat OpenImg;
        // OpenImg = cv::imread(m_strFileName.toLocal8Bit().data());
        // m_imgSrc = QImage(OpenImg.data, OpenImg.cols, OpenImg.rows, OpenImg.step, QImage::Format_BGR888).copy();
        m_img2Show = m_imgSrc.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        m_pix2Show = QPixmap::fromImage(m_img2Show);
        if(m_rotate_flag){
            QTransform transform;
            transform.rotate(270);
            m_pix2Show = m_pix2Show.transformed(transform);
        }
        ui->label->setPixmap(m_pix2Show);
    }
}

