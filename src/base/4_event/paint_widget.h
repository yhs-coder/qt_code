﻿#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

signals:
};

#endif // PAINT_WIDGET_H
