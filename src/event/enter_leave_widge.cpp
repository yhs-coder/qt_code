#include "enter_leave_widget.h"

#include <QLabel>
#include <QVBoxLayout>

EnterLeaveWidget::EnterLeaveWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* lbl = new QLabel(this);
    lbl->setText("鼠标进入/离开");
    lbl->setFrameShape(QFrame::Box);
    lbl->setFixedHeight(50);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setStyleSheet("background-color: blue;color: white;font-size: 25px");
    verticalLayout->addWidget(lbl);
}

