#ifndef PROPAGATE_LABEL_H
#define PROPAGATE_LABEL_H

#include <QLabel>
#include <QWidget>

class PropagateLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PropagateLabel(QWidget* parent = nullptr);

private:
    void mousePressEvent(QMouseEvent* event) override;
    //  重写事件分发
    bool event(QEvent* e) override;
};

#endif  // PROPAGATE_LABEL_H
