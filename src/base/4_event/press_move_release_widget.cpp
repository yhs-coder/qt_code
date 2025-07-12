#include "press_move_release_widget.h"

#include <QDebug>
#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "label.h"

PressMoveReleaseWidget::PressMoveReleaseWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    // 1. 添加自定义标签控件
    Label* label = new Label(this);
    label->setText("鼠标按下/移动/释放");
    label->setFrameShape(QFrame::Box);
    label->setFixedHeight(60);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(R"(
        background-color: blue;
        color: white;
        font-size: 25px
    )");

    verticalLayout->addWidget(label);

    // 2. 添加一个标准的标签控件
    m_widget = new QWidget(this);
    m_label  = new QLabel(m_widget);
    m_label->setFixedSize(100, 100);
    m_label->setText("");
    m_label->setFrameShape(QFrame::Box);
    // m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet(R"(
        background-color: green;
    )");

    verticalLayout->addWidget(m_widget);

    // 安装时间过滤器
    m_label->installEventFilter(this);
}

void PressMoveReleaseWidget::boundaryProcess(QPoint& dstPos)
{
    // 计算窗口边界限制
    int xMin = 0;
    int xMax = m_widget->width() - m_label->width();
    int yMin = 0;
    int yMax = m_widget->height() - m_label->height();

    // 限制目标位置在窗口内
    dstPos.setX(qMax(qMin(dstPos.x(), xMax), xMin));
    dstPos.setY(qMax(qMin(dstPos.y(), yMax), yMin));

    // // 超出最左边
    // if (m_label->pos().x() < 0) {
    //     m_label->move(0, dstPos.y());
    //     return false;
    // }

    // // 在当前窗口下，x最大取值
    // int xMax = m_widget->width() - m_label->width();
    // // qDebug() << " m_widget->width() = " << m_widget->width() << "m_label->width()" << m_label->width();
    // // 超出最右边
    // if (m_label->pos().x() > xMax) {
    //     m_label->move(xMax, dstPos.y());
    //     return false;
    // }
    // // 超出最上边
    // if (m_label->pos().y() < 0) {
    //     m_label->move(dstPos.x(), 0);
    //     return false;
    // }
    // //  在当前窗口下，y最大取值
    // int yMax = m_widget->height() - m_label->height();
    // // 超出最下边
    // if (m_label->pos().y() > yMax) {
    //     m_label->move(dstPos.x(), yMax);
    //     return false;
    // }
    // // 不超出边界
    // return true;
}

bool PressMoveReleaseWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != m_label) {
        return QWidget::eventFilter(watched, event);
    }
    if (event->type() == QEvent::MouseButtonPress) {
        qDebug() << "MouseButtonPress";
        // 记录鼠标按下的位置、当前标签的位置
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        m_pressPos              = mouseEvent->globalPos();
        m_wndPos                = m_label->pos();
        qDebug() << m_wndPos;
    } else if (event->type() == QEvent::MouseMove) {
        qDebug() << "MouseMove";
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint       dstPos     = m_wndPos + (mouseEvent->globalPos() - m_pressPos);
        // 禁止移动出窗口
        boundaryProcess(dstPos);
        m_label->move(dstPos);

    } else if (event->type() == QEvent::MouseButtonRelease) {
        qDebug() << "MouseButtonRelease";
    }
}
