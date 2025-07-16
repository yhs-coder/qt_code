#include "propagate_widget.h"

#include <QDebug>
#include <QEvent>
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
    )");

    verticalLayout->addWidget(m_lbl);

    m_lbl->installEventFilter(this);
}

void PropagateWidget::mousePressEvent(QMouseEvent* event) { qDebug() << "PropagateWidget::mousePressEvent"; }

bool PropagateWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_lbl && event->type() == QEvent::MouseButtonPress) {
        qDebug() << "PropagateWidget::eventFilter";

        // 返回 true：则事件到此为止，不再向下传递，也就是不再传递到对应的控件
        // return true;
        // 返回 false：则事件继续传递，也就是接着会传递到对应的控件
        // 等价于 return QWidget::eventFilter(watched, event);
        // return false;
    }
    return QWidget::eventFilter(watched, event);
}
