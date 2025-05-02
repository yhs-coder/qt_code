#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QIntValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置验证器，只允许文本框输入整数
    ui->leAdd1->setValidator(new QIntValidator(this));
    ui->leAdd2->setValidator(new QIntValidator(this));
    ui->leAdd1->setPlaceholderText("加数");
    ui->leAdd2->setPlaceholderText("被加数");
    ui->leSum->setPlaceholderText("和");

    ui->leSub1->setValidator(new QIntValidator(this));
    ui->leSub2->setValidator(new QIntValidator(this));
    ui->leSub1->setPlaceholderText("减数");
    ui->leSub2->setPlaceholderText("被减数");
    ui->leResult->setPlaceholderText("差");
}

Widget::~Widget()
{
    delete ui;
}

// 正常模式
void Widget::on_btnEchoNormal_clicked()
{
    // 清空文本框的内容
    ui->leEcho->clear();

    // 文本框的回显模式设置成正常
    ui->leEcho->setEchoMode(QLineEdit::Normal);
    // 设置占位字符串为normal
    ui->leEcho->setPlaceholderText("Normal");
}


void Widget::on_btnEchoPassword_clicked()
{
    ui->leEcho->clear();

    // 文本框的回显模式设置成密码模式,即不显示实际输入的字符，用小圆圈代替
    ui->leEcho->setEchoMode(QLineEdit::Password);
    ui->leEcho->setPlaceholderText("Password");
}


void Widget::on_btnEchoNoEcho_clicked()
{
    ui->leEcho->clear();

    // 文本框的回显模式设置成无回显模式,即不显示输入的内容
    ui->leEcho->setEchoMode(QLineEdit::NoEcho);
    ui->leEcho->setPlaceholderText("NoEcho");
}


void Widget::on_btnEchoPasswordEchoOnEdit_clicked()
{
    ui->leEcho->clear();

    // 文本框失去焦点时以密码模式显示
    ui->leEcho->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->leEcho->setPlaceholderText("PasswordEchoOnEdit");
}


void Widget::on_btnEchoPrint_clicked()
{
    QMessageBox::information(this, "文本框内容", ui->leEcho->text());
}

// 文本框文本左对齐
void Widget::on_btnAlignLeft_clicked()
{
    ui->leAlignment->setAlignment(Qt::AlignLeft);
    ui->leAlignment->setPlaceholderText("Left");
}

// 文本框文本居中对齐
void Widget::on_btnAlignCenter_clicked()
{
    ui->leAlignment->setAlignment(Qt::AlignCenter);
    ui->leAlignment->setPlaceholderText("Center");
}

// 文本框文本右对齐
void Widget::on_btnAlignRight_clicked()
{
    ui->leAlignment->setAlignment(Qt::AlignRight);
    ui->leAlignment->setPlaceholderText("Right");
}

// 文本访问控制可读可写
void Widget::on_btnAccessReadWrite_clicked()
{
    ui->leAccess->setReadOnly(false);
    ui->leAccess->setPlaceholderText("ReadWrite");
}

// 只可读
void Widget::on_btnAccessReadOnly_clicked()
{
    ui->leAccess->setReadOnly(true);
    ui->leAccess->setPlaceholderText("ReadOnly");
}


void Widget::on_btnAccessDisabled_clicked()
{
    ui->leAccess->setEnabled(false);
    ui->leAccess->setPlaceholderText("Disabled");
}


void Widget::on_btnAccessEnabled_clicked()
{
    ui->leAccess->setEnabled(true);
    ui->leAccess->setPlaceholderText("Enabled");
}

// 没有设置文本格式
void Widget::on_btnMaskNone_clicked()
{
    // "" 表示接受任何字符的输入
    ui->leMask->setInputMask("");
}


void Widget::on_btnMaskPhone_clicked()
{
    // 9 - 表示要求输入0-9的数字
    // ; - 表示格式字符串结束，
    // # - 未输入时(占位字符)显示#
    ui->leMask->setInputMask("99999999999;#");
}


void Widget::on_btnMaskLicense_clicked()
{
    // > - 表示字母转换为大写
    // A - 表示要求输入英文字母
    // ; - 表示格式字符串结束，
    // # - 未输入时(占位字符)显示#
    ui->leMask->setInputMask(">AAAAA-AAAAA-AAAAA-AAAAA-AAAAA;#");
    ui->leMask->clear();
}


void Widget::on_leAdd1_textChanged(const QString &arg1)
{
    int sum = arg1.toInt() + ui->leAdd2->text().toInt();
    ui->leSum->setText(QString::number(sum));
}


void Widget::on_leAdd2_textChanged(const QString &arg1)
{
    int sum = arg1.toInt() + ui->leAdd1->text().toInt();
    ui->leSum->setText(QString::number(sum));
}


void Widget::on_leSub1_editingFinished()
{
    int result = ui->leSub1->text().toInt() - ui->leSub2->text().toInt();
    ui->leResult->setText(QString::number(result));
}


void Widget::on_leSub2_editingFinished()
{
    int result = ui->leSub1->text().toInt() - ui->leSub2->text().toInt();
    ui->leResult->setText(QString::number(result));
}

