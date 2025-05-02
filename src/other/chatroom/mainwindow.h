#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/************************************************
*
* @file     mainwindow.h
* @brief    主窗口
* @author   yhs-coder
* @brief    xxx Function
* @date     2024/04/18
*
************************************************/




#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
