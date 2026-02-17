/********************************************************************************
** Form generated from reading UI file 'remove_pic_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVE_PIC_DIALOG_H
#define UI_REMOVE_PIC_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Remove_Pic_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *Remove_Pic_Dialog)
    {
        if (Remove_Pic_Dialog->objectName().isEmpty())
            Remove_Pic_Dialog->setObjectName(QString::fromUtf8("Remove_Pic_Dialog"));
        Remove_Pic_Dialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Remove_Pic_Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 193, 351, 91));
        buttonBox->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(23);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        label = new QLabel(Remove_Pic_Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 90, 421, 21));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label_2 = new QLabel(Remove_Pic_Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 130, 421, 21));
        label_2->setFont(font1);

        retranslateUi(Remove_Pic_Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Remove_Pic_Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Remove_Pic_Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Remove_Pic_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Remove_Pic_Dialog)
    {
        Remove_Pic_Dialog->setWindowTitle(QCoreApplication::translate("Remove_Pic_Dialog", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        buttonBox->setToolTip(QCoreApplication::translate("Remove_Pic_Dialog", "<html><head/><body><p>OK</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        buttonBox->setWhatsThis(QCoreApplication::translate("Remove_Pic_Dialog", "<html><head/><body><p>OK</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QCoreApplication::translate("Remove_Pic_Dialog", "Are you sure you want to", nullptr));
        label_2->setText(QCoreApplication::translate("Remove_Pic_Dialog", "delete this picture?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Remove_Pic_Dialog: public Ui_Remove_Pic_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVE_PIC_DIALOG_H
