#ifndef DRAG_WIDGET_H
#define DRAG_WIDGET_H

#include <QWidget>

class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);

signals:
};

#endif  // DRAG_WIDGET_H
