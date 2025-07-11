#include "paint_widget.h"

#include <QLabel>
#include <QVBoxLayout>

PaintWidget::PaintWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* label = new QLabel(this);
    label->setText("绘图事件");
    label->setFrameShape(QFrame::Box);
    label->setFixedHeight(60);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(R"(
        background-color: blue;
        color: white;
        font-size: 25px
    )");

    verticalLayout->addWidget(label);
}
