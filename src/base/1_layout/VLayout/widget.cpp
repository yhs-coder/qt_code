#include "widget.h"

#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton *pBtn1 = new QPushButton(this);
    pBtn1->setObjectName("pBtn1");
    pBtn1->setText("btn1");
    // pBtn1->setFixedSize(40, 32);

    QPushButton *pBtn2 = new QPushButton(this);
    pBtn2->setObjectName("pBtn2");
    pBtn2->setText("btn2");
    // pBtn2->setFixedSize(40, 32);

    QPushButton *pBtn3 = new QPushButton(this);
    pBtn3->setObjectName("pBtn3");
    pBtn3->setText("btn3");
    // pBtn3->setFixedSize(40, 32);

    QVBoxLayout *pVLay = new QVBoxLayout(this);
    pVLay->setMargin(30);
    pVLay->addWidget(pBtn1);
    // pVLay->addSpacing(30);
    pVLay->addWidget(pBtn2);
    // pVLay->addSpacing(50);
    pVLay->addWidget(pBtn3);
    pVLay->setContentsMargins(80, 70, 60, 50);
}

Widget::~Widget() {}
