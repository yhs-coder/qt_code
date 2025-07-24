#include "widget.h"

#include "./ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();
}

Widget::~Widget() { delete ui; }

void Widget::initUI()
{
    // 1. 形状
    ui->cboShape->addItem("Point", static_cast<int>(_Point));
    ui->cboShape->addItem("Line", static_cast<int>(_Line));

    ui->cboShape->addItem("Rectangle", static_cast<int>(_Rect));
    ui->cboShape->addItem("Rounded Rectangle", static_cast<int>(_RoundedRect));
    ui->cboShape->addItem("Ellipse", static_cast<int>(_Ellipse));

    ui->cboShape->addItem("Arc", static_cast<int>(_Arc));
    ui->cboShape->addItem("Pie", static_cast<int>(_Pie));
    ui->cboShape->addItem("Chord", static_cast<int>(_Chord));

    ui->cboShape->addItem("Polyline", static_cast<int>(_Polyline));
    ui->cboShape->addItem("Polygon", static_cast<int>(_Polygon));

    ui->cboShape->addItem("Path", static_cast<int>(_Path));

    ui->cboShape->addItem("Text", static_cast<int>(_Text));
    ui->cboShape->addItem("Pixmap", static_cast<int>(_Pixmap));
}
