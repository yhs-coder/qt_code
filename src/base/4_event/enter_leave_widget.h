#ifndef ENTER_LEAVE_WIDGET_H
#define ENTER_LEAVE_WIDGET_H

#include <QLabel>
#include <QWidget>

class EnterLeaveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnterLeaveWidget(QWidget* parent = nullptr);

private:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QLabel* m_label;
signals:
};

#endif  // ENTER_LEAVE_WIDGET_H
