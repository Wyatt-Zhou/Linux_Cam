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
    QPushButton *TBDBtn;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *PrePicBtn;
    QPushButton *NextPicBtn;

    void setupUi(QWidget *CamWindow)
    {
        if (CamWindow->objectName().isEmpty())
            CamWindow->setObjectName(QString::fromUtf8("CamWindow"));
        CamWindow->resize(800, 1280);
        label = new QLabel(CamWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 60, 800, 561));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(800, 200));
        label->setMaximumSize(QSize(800, 1000));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);"));
        label->setAlignment(Qt::AlignCenter);
        ReturnBtn = new QPushButton(CamWindow);
        ReturnBtn->setObjectName(QString::fromUtf8("ReturnBtn"));
        ReturnBtn->setGeometry(QRect(0, 0, 60, 60));
        ReturnBtn->setMinimumSize(QSize(60, 60));
        ReturnBtn->setMaximumSize(QSize(60, 60));
        horizontalLayoutWidget = new QWidget(CamWindow);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 620, 801, 221));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        AlbumBtn = new QPushButton(horizontalLayoutWidget);
        AlbumBtn->setObjectName(QString::fromUtf8("AlbumBtn"));
        AlbumBtn->setMinimumSize(QSize(60, 60));
        AlbumBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout->addWidget(AlbumBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        TakePhoto = new QPushButton(horizontalLayoutWidget);
        TakePhoto->setObjectName(QString::fromUtf8("TakePhoto"));
        TakePhoto->setMinimumSize(QSize(80, 80));
        TakePhoto->setMaximumSize(QSize(60, 60));

        horizontalLayout->addWidget(TakePhoto);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        TBDBtn = new QPushButton(horizontalLayoutWidget);
        TBDBtn->setObjectName(QString::fromUtf8("TBDBtn"));
        TBDBtn->setMinimumSize(QSize(60, 60));
        TBDBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout->addWidget(TBDBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        PrePicBtn = new QPushButton(CamWindow);
        PrePicBtn->setObjectName(QString::fromUtf8("PrePicBtn"));
        PrePicBtn->setGeometry(QRect(0, 500, 80, 120));
        NextPicBtn = new QPushButton(CamWindow);
        NextPicBtn->setObjectName(QString::fromUtf8("NextPicBtn"));
        NextPicBtn->setGeometry(QRect(720, 500, 80, 120));

        retranslateUi(CamWindow);

        QMetaObject::connectSlotsByName(CamWindow);
    } // setupUi

    void retranslateUi(QWidget *CamWindow)
    {
        CamWindow->setWindowTitle(QCoreApplication::translate("CamWindow", "CamWindow", nullptr));
        label->setText(QCoreApplication::translate("CamWindow", "TextLabel", nullptr));
        ReturnBtn->setText(QCoreApplication::translate("CamWindow", "Return", nullptr));
        AlbumBtn->setText(QCoreApplication::translate("CamWindow", "Album", nullptr));
        TakePhoto->setText(QCoreApplication::translate("CamWindow", "Takephoto", nullptr));
        TBDBtn->setText(QCoreApplication::translate("CamWindow", "TBD", nullptr));
        PrePicBtn->setText(QCoreApplication::translate("CamWindow", "Previous", nullptr));
        NextPicBtn->setText(QCoreApplication::translate("CamWindow", "next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CamWindow: public Ui_CamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMWINDOW_H
