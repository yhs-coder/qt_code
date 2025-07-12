#include "enter_leave_widget.h"

#include <QDebug>
#include <QEvent>
#include <QLabel>
#include <QVBoxLayout>

#include "label.h"

EnterLeaveWidget::EnterLeaveWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    // 1. 添加一个自定义的标签控件,通过重写鼠标进入/离开事件实现
    Label* label = new Label(this);
    // QLabel* label = new QLabel(this);
    // label->setText("鼠标进入/离开");
    label->setText("");
    label->setFrameShape(QFrame::Box);
    label->setFixedHeight(60);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(R"(
        background-color: blue;
        color: white;
        font-size: 25px
    )");

    verticalLayout->addWidget(label);

    // 添加一个自定义的标签控件
    m_label = new QLabel(this);
    // QLabel* label = new QLabel(this);
    // label->setText("鼠标进入/离开");
    m_label->setText("");
    m_label->setFrameShape(QFrame::Box);
    m_label->setFixedHeight(60);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet(R"(
        background-color: red;
        color: white;
        font-size: 25px
    )");

    verticalLayout->addWidget(m_label);

    // 2. 通过安装事件过滤器实现
    // 需要重写eventFilter函数,决定当前是否对象截获/过滤事件，返回true则表示将该事件截获，不发送给标签
    // 返回false则将事件传递给监控（目标）对象 -> 标签
    m_label->installEventFilter(this);
}

static int cnt = 0;

bool EnterLeaveWidget::eventFilter(QObject* watched, QEvent* event)
{
    // 监控对象是标签控件
    if (watched == m_label) {
        // 判断事件类型是进入还是离开
        if (event->type() == QEvent::Enter) {
            m_label->setText(QString("enterEvent: %1").arg(++cnt));
        } else if (event->type() == QEvent::Leave) {
            m_label->setText(QString("leaveEvent: %1").arg(++cnt));
        }
    }
    // qDebug() << QWidget::eventFilter(watched, event); // 返回false，事件交由标签对象处理
    return QWidget::eventFilter(watched, event);
}
