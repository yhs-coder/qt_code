#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QWidget* navWidget;

    QWidget* mainWidget;
    QStackedWidget* stackedWidget;
};
#endif // MAINWIDGET_H
