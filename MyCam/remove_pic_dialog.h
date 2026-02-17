#ifndef REMOVE_PIC_DIALOG_H
#define REMOVE_PIC_DIALOG_H

#include <QDialog>

namespace Ui {
class Remove_Pic_Dialog;
}

class Remove_Pic_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Remove_Pic_Dialog(QWidget *parent = nullptr);
    ~Remove_Pic_Dialog();

private:
    Ui::Remove_Pic_Dialog *ui;
};

#endif // REMOVE_PIC_DIALOG_H
