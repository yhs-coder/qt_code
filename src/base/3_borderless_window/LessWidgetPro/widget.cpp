#include "widget.h"

#include <QVBoxLayout>
// #include "./ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent)
// , ui(new Ui::Widget)
{
    // ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    initUI();
}

Widget::~Widget()
{
    // delete ui;
}

void Widget::initUI()
{
    QWidget* widget = new QWidget(this);
    m_pTitleBar     = new CTitleBar(this);

    widget->setMinimumSize(400, 400);

    QVBoxLayout* pVlay = new QVBoxLayout(this);

    pVlay->addWidget(m_pTitleBar);
    pVlay->addWidget(widget);
}
