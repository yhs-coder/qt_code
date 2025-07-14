#ifndef TIMER_WIDGET_H
#define TIMER_WIDGET_H

#include <QLabel>
#include <QWidget>

class TimerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimerWidget(QWidget* parent = nullptr);

protected:
    // 重写timerEvent定时器事件
    void timerEvent(QTimerEvent* event) override;

private slots:
    void onStartClicked();
    void onStopClicked();
    void onResetClicked();

    // 定时器类的槽函数
    void onTimeout1();
    void onTimeout2();

private:
    QLabel* m_label1;
    QLabel* m_label2;

    int m_id1;
    int m_id2;

    QTimer* m_timer1;
    QTimer* m_timer2;
};

#endif  // TIMER_WIDGET_H
