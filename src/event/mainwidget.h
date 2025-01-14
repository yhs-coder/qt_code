#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QPushButton>
#include "enter_leave_widget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initNav();
    void initMain(); // 右侧的子界面

private:
    QWidget* navWidget;

    QWidget* mainWidget;
    QStackedWidget* stackedWidget;
    QButtonGroup* btnGroup;
};
#endif // MAINWIDGET_H
