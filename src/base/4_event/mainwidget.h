#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QButtonGroup>
#include <QStackedWidget>
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    // 初始化界面
    void initUI();

    // 初始化左侧导航栏
    void initNav();

    // 初始化右侧窗口
    void initMain();

private slots:
    void buttonClicked();

private:
    QWidget*        m_navWidget;      // 左侧导航
    QButtonGroup*   m_btnGroup;       // 按钮组
    QWidget*        m_mainWidget;     // 右侧界面
    QStackedWidget* m_stackedWidget;  // 堆栈窗口，用于切换页面
};
#endif  // MAINWIDGET_H
