#ifndef CAMWINDOW_H
#define CAMWINDOW_H

#include <QWidget>
#include <QDir>
#include <QTextStream>
#include "threadgetcampic.h"
#include "mpu_compiler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CamWindow;
}
QT_END_NAMESPACE

class CamWindow : public QWidget
{
    Q_OBJECT

public:
    CamWindow(QWidget *parent = nullptr);
    ~CamWindow();

private:
    Ui::CamWindow *ui;

    QImage m_imgSrc;
    QImage m_img2Show;
    QPixmap m_pix2Show;

    QString m_album_path;
    QStringList m_all_pic_path;

    QString m_dateTime;
    QString m_picname;
    QString m_picpath;

    QString m_strFileName;

    ThreadGetCamPIc m_stThreadGetCamPic;

    MPU_CompilerController *compilerController = NULL;

    int m_pic_count;
    int m_pic_sequence;
    bool m_push_takephoto_flag;
    bool m_rotate_flag;
    bool m_static_pic_rotate_flag;

private slots:
    void OpenAlbum();
    void Return2Cam();
    void ShowPreviousPic();
    void ShowNextPic();

    void onFreshCurImg(const QImage& img);
    void CamOpenError();
    void SavePic2Album();
    void StopShowPic();

    void DeletePic();

    void RecordVideo();
    void PlayRecVideo();
    void VideoPlayEnd();

    void RotateLabel(const bool rotate_flag);
};
#endif // CAMWINDOW_H
