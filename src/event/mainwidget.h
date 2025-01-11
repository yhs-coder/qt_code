#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QPushButton>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initNav();

private:
    QWidget* navWidget;

    QWidget* mainWidget;
    QStackedWidget* stackedWidget;
    QButtonGroup* btnGroup;
};
#endif // MAINWIDGET_H
