#include "timer_widget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QVBoxLayout>

TimerWidget::TimerWidget(QWidget* parent) : QWidget{parent}
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    m_label1 = new QLabel(this);
    m_label1->setText("");
    m_label1->setFrameShape(QFrame::Box);
    m_label1->setFixedSize(100, 100);
    m_label1->setStyleSheet(R"(
        background-color: blue;
    )");

    m_label2 = new QLabel(this);
    m_label2->setText("");
    m_label2->setFrameShape(QFrame::Box);
    m_label2->setFixedSize(100, 100);
    m_label2->setStyleSheet(R"(
        background-color: red;
    )");

    verticalLayout->addWidget(m_label1);
    verticalLayout->addWidget(m_label2);

    // 添加三个操作按钮
    QPushButton* btnStart = new QPushButton(this);
    btnStart->setText("开始");
    QPushButton* btnStop = new QPushButton(this);
    btnStop->setText("停止");
    QPushButton* btnReset = new QPushButton(this);
    btnReset->setText("复位");

    QHBoxLayout* horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(20);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // 三个按钮水平布局
    horizontalLayout->addWidget(btnStart);
    horizontalLayout->addWidget(btnStop);
    horizontalLayout->addWidget(btnReset);

    // 使用addLayout(),让水平布局的生命周期由垂直布局管理。
    // 当垂直布局被销毁时，它会自动销毁其所有子布局和子控件，包括水平布局。
    verticalLayout->addLayout(horizontalLayout);
    this->setStyleSheet(R"(
        QPushButton {
            font-size: 24px;
        }
      )");

    connect(btnStart, &QPushButton::clicked, this, &TimerWidget::onStartClicked);
    connect(btnStop, &QPushButton::clicked, this, &TimerWidget::onStopClicked);
    connect(btnReset, &QPushButton::clicked, this, &TimerWidget::onResetClicked);

    // 使用定时器类处理
    m_timer1 = new QTimer(this);
    m_timer2 = new QTimer(this);
    connect(m_timer1, &QTimer::timeout, this, &TimerWidget::onTimeout1);
    connect(m_timer2, &QTimer::timeout, this, &TimerWidget::onTimeout2);
}

void TimerWidget::timerEvent(QTimerEvent* event)
{
    // 获取定时器的定时时间
    if (event->timerId() == m_id1) {
        m_label1->move(m_label1->x() + 10, m_label1->y());
        // 当标签超出当前窗口，重新回到最左侧
        if (m_label1->x() >= this->width()) {
            m_label1->move(0, m_label1->y());
        }
    } else if (event->timerId() == m_id2) {
        m_label2->move(m_label2->x() + 10, m_label2->y());
        if (m_label2->x() >= this->width()) {
            m_label2->move(0, m_label2->y());
        }
    }
}

void TimerWidget::onStartClicked()
{
#ifdef USE_TIMER_EVENT
    // 定时器事件方式，启动定时器
    m_id1 = startTimer(10);  // 时间间隔10ms
    m_id2 = startTimer(20);  // 时间间隔10ms
#else
    // 使用QTimer类，启动定时器
    m_timer1->start(10);
    m_timer2->start(20);
#endif
}

void TimerWidget::onStopClicked()
{
#ifdef USE_TIMER_EVENT
    // 销毁指定定时时间的定时器
    killTimer(m_id1);
    killTimer(m_id2);
#else
    m_timer1->stop();
    m_timer2->stop();
#endif
}

void TimerWidget::onResetClicked()
{
    m_label1->move(0, m_label1->y());
    m_label2->move(0, m_label2->y());
}

void TimerWidget::onTimeout1()
{
    m_label1->move(m_label1->x() + 10, m_label1->y());
    // 当标签超出当前窗口，重新回到最左侧
    if (m_label1->x() >= this->width()) {
        m_label1->move(0, m_label1->y());
    }
}

void TimerWidget::onTimeout2()
{
    m_label2->move(m_label2->x() + 10, m_label2->y());
    if (m_label2->x() >= this->width()) {
        m_label2->move(0, m_label2->y());
    }
}
