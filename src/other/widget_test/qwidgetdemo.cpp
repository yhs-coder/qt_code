#include "qwidgetdemo.h"
#include "ui_qwidgetdemo.h"
#include <QDebug>

QWidgetDemo::QWidgetDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QWidgetDemo)
{
    ui->setupUi(this);
}

QWidgetDemo::~QWidgetDemo()
{
    qDebug() << "destroy subwidget";
    delete ui;
}

void QWidgetDemo::on_btnGetSize_clicked()
{
    qDebug() << "-------------------------------";
    QRect rect = this->geometry();
    qDebug() << "topLeft: " << rect.topLeft();
    qDebug() << "topRight: " << rect.topRight();
    qDebug() << "bottomLeft: " << rect.bottomLeft();
    qDebug() << "bottomRight: " << rect.bottomRight();
    qDebug() << "width: " << rect.width();
    qDebug() << "height: " << rect.height();
}


void QWidgetDemo::on_btnSetSize_clicked()
{
    this->resize(400,400);
}


void QWidgetDemo::on_btnSetFixedSize_clicked()
{
    this->setFixedSize(500,500);
}


void QWidgetDemo::on_btnSetMaxSize_clicked()
{
    this->setMaximumSize(600, 600);
}


void QWidgetDemo::on_btnSetMinSize_clicked()
{
    this->setMinimumSize(300, 300);
}


void QWidgetDemo::on_btnMove_clicked()
{
    this->move(100, 100);
}


void QWidgetDemo::on_btnSetTitle_clicked()
{
    this->setWindowTitle("test QWidget");
}


void QWidgetDemo::on_btnSetIcon_clicked()
{
    this->setWindowIcon(QIcon(":/icon/icon.ico"));
}

