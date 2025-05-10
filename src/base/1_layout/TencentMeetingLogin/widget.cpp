#include "widget.h"

#include <QSize>

#include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置无边框，点击应用程序可切换成隐藏/显示
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->setStyleSheet("background-color: white; border:none");

    ui->btnSet->setText("");
    ui->btnSet->setStyleSheet(
        "QPushButton{background-image:url(:/resources/set.png); border:none} \
        QPushButton::hover{background-color:rgba(20, 122, 255, 0.1)}");

    ui->btnMin->setText("");
    ui->btnMin->setStyleSheet(
        "QPushButton{background-image:url(:/resources/min.png); border:none} \
        QPushButton::hover{background-color:rgba(20, 122, 255, 0.1)}");

    ui->btnClose->setText("");
    ui->btnClose->setStyleSheet(
        "QPushButton{background-image:url(:/resources/close.png); border:none} \
        QPushButton::hover{background-color:rgba(20, 122, 255, 0.1)}");

    ui->label_logo->clear();
    QPixmap* pix = new QPixmap(":/resources/logo.png");
    pix->scaled(ui->label_logo->size(), Qt::KeepAspectRatio);
    ui->label_logo->setScaledContents(true);
    ui->label_logo->setPixmap(*pix);

    ui->toolBtnPhone->setIcon(QIcon(":/resources/phonelogin.png"));
    ui->toolBtnPhone->setIconSize(QSize(68, 60));
    ui->toolBtnPhone->setText("手机号");
    ui->toolBtnPhone->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBtnPhone->setStyleSheet("background-color: white; border:none");

    ui->toolBtnEnpirseWX->setIcon(QIcon(":/resources/enpriseweichat.png"));
    ui->toolBtnEnpirseWX->setIconSize(QSize(68, 60));
    ui->toolBtnEnpirseWX->setText("企业微信");
    ui->toolBtnEnpirseWX->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBtnEnpirseWX->setStyleSheet("background-color: white; border:none");

    ui->toolBtnSSO->setIcon(QIcon(":/resources/sso.png"));
    ui->toolBtnSSO->setIconSize(QSize(68, 60));
    ui->toolBtnSSO->setText("SSO");
    ui->toolBtnSSO->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolBtnSSO->setStyleSheet("background-color: white; border:none");

    connect(ui->btnClose, &QPushButton::clicked, [=]() { close(); });
}

Widget::~Widget() { delete ui; }
