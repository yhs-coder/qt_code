#include "propagate_widget.h"

#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

PropagateWidget::PropagateWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    m_lbl = new PropagateLabel(this);
    m_lbl->setFrameShape(QFrame::Box);
    m_lbl->setFixedHeight(60);
    m_lbl->setStyleSheet(R"(
        background-color: blue;
        color: white;
        font-size: 25px
    )");

    verticalLayout->addWidget(m_lbl);
}

void PropagateWidget::mousePressEvent(QMouseEvent* event) { qDebug() << "PropagateWidget::mousePressEvent"; }
