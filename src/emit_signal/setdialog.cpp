#include "setdialog.h"

#include "ui_setdialog.h"

SetDialog::SetDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SetDialog) { ui->setupUi(this); }

SetDialog::~SetDialog() { delete ui; }

void SetDialog::on_btnAdd_clicked()
{
    static int num = 90;
    // 发射信号
    emit sig_addOne(num++);
}
