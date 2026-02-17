/********************************************************************************
** Form generated from reading UI file 'camwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMWINDOW_H
#define UI_CAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CamWindow
{
public:
    QLabel *label;
    QPushButton *ReturnBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *AlbumBtn;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *TakePhoto;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *RecordBtn;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PrePicBtn;
    QPushButton *NextPicBtn;
    QPushButton *DeleteBtn;
    QPushButton *PlayBtn;

    void setupUi(QWidget *CamWindow)
    {
        if (CamWindow->objectName().isEmpty())
            CamWindow->setObjectName(QString::fromUtf8("CamWindow"));
        CamWindow->resize(800, 1280);
        label = new QLabel(CamWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 60, 800, 1000));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(800, 200));
        label->setMaximumSize(QSize(800, 1000));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignCenter);
        ReturnBtn = new QPushButton(CamWindow);
        ReturnBtn->setObjectName(QString::fromUtf8("ReturnBtn"));
        ReturnBtn->setGeometry(QRect(0, 0, 60, 60));
        ReturnBtn->setMinimumSize(QSize(60, 60));
        ReturnBtn->setMaximumSize(QSize(60, 60));
        ReturnBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/back.png);"));
        horizontalLayoutWidget = new QWidget(CamWindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 1060, 801, 221));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        AlbumBtn = new QPushButton(horizontalLayoutWidget);
        AlbumBtn->setObjectName(QString::fromUtf8("AlbumBtn"));
        AlbumBtn->setMinimumSize(QSize(60, 60));
        AlbumBtn->setMaximumSize(QSize(60, 60));
        AlbumBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/album.png);"));

        horizontalLayout->addWidget(AlbumBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        TakePhoto = new QPushButton(horizontalLayoutWidget);
        TakePhoto->setObjectName(QString::fromUtf8("TakePhoto"));
        TakePhoto->setMinimumSize(QSize(120, 120));
        TakePhoto->setMaximumSize(QSize(120, 120));
        TakePhoto->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/take_photo.png);"));

        horizontalLayout->addWidget(TakePhoto);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        RecordBtn = new QPushButton(horizontalLayoutWidget);
        RecordBtn->setObjectName(QString::fromUtf8("RecordBtn"));
        RecordBtn->setMinimumSize(QSize(80, 80));
        RecordBtn->setMaximumSize(QSize(80, 80));
        RecordBtn->setCheckable(true);

        horizontalLayout->addWidget(RecordBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PrePicBtn = new QPushButton(CamWindow);
        PrePicBtn->setObjectName(QString::fromUtf8("PrePicBtn"));
        PrePicBtn->setGeometry(QRect(0, 500, 80, 80));
        PrePicBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/left.png);"));
        NextPicBtn = new QPushButton(CamWindow);
        NextPicBtn->setObjectName(QString::fromUtf8("NextPicBtn"));
        NextPicBtn->setGeometry(QRect(720, 500, 80, 80));
        NextPicBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/right.png);"));
        DeleteBtn = new QPushButton(CamWindow);
        DeleteBtn->setObjectName(QString::fromUtf8("DeleteBtn"));
        DeleteBtn->setGeometry(QRect(740, 0, 60, 60));
        DeleteBtn->setMinimumSize(QSize(60, 60));
        DeleteBtn->setMaximumSize(QSize(60, 60));
        DeleteBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/garbage.png);"));
        PlayBtn = new QPushButton(CamWindow);
        PlayBtn->setObjectName(QString::fromUtf8("PlayBtn"));
        PlayBtn->setGeometry(QRect(330, 400, 150, 150));
        PlayBtn->setMinimumSize(QSize(150, 150));
        PlayBtn->setMaximumSize(QSize(150, 150));
        PlayBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/icon/play.png);"));

        retranslateUi(CamWindow);

        QMetaObject::connectSlotsByName(CamWindow);
    } // setupUi

    void retranslateUi(QWidget *CamWindow)
    {
        CamWindow->setWindowTitle(QCoreApplication::translate("CamWindow", "CamWindow", nullptr));
        label->setText(QCoreApplication::translate("CamWindow", "TextLabel", nullptr));
        ReturnBtn->setText(QString());
        AlbumBtn->setText(QString());
        TakePhoto->setText(QString());
        RecordBtn->setText(QString());
        PrePicBtn->setText(QString());
        NextPicBtn->setText(QString());
        DeleteBtn->setText(QString());
        PlayBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CamWindow: public Ui_CamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMWINDOW_H
