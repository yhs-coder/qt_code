#ifndef PROPAGATE_WIDGET_H
#define PROPAGATE_WIDGET_H

#include <QWidget>

#include "propagate_label.h"

class PropagateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropagateWidget(QWidget* parent = nullptr);

private:
    void mousePressEvent(QMouseEvent* event) override;

private:
    PropagateLabel* m_lbl;
};

#endif  // PROPAGATE_WIDGET_H
