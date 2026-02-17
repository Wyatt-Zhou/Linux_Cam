#include "remove_pic_dialog.h"
#include "ui_remove_pic_dialog.h"

Remove_Pic_Dialog::Remove_Pic_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Remove_Pic_Dialog)
{
    ui->setupUi(this);
}

Remove_Pic_Dialog::~Remove_Pic_Dialog()
{
    delete ui;
}
