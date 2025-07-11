#ifndef CONTEXT_WIDGET_H
#define CONTEXT_WIDGET_H

#include <QWidget>

class ContextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContextWidget(QWidget *parent = nullptr);

signals:
};

#endif // CONTEXT_WIDGET_H
