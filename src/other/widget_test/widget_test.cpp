#include "widget_test.h"
#include "winstate.h"
#include "qwidgetdemo.h"

widget_test::widget_test(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(this, &widget_test::Hide, this, &QWidget::hide);

    // 去除界面边框和标题栏，生成无边框窗口
    // this->setWindowFlags(Qt::FramelessWindowHint);

    // 设置窗口的标志
    // 取消关闭按钮，使其不可用
    // this->setWindowFlag(Qt::WindowCloseButtonHint, false);

    // 取消最小化按钮，使其不可用
    // this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);

    // 取消最小化按钮，使其不可用
    // this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    // 标签栏保留，去除所有按钮
    // this->setWindowFlags(Qt::WindowTitleHint  | Qt::CustomizeWindowHint);


    WinState *state = new WinState();
    state->show();

    //------------------------------------------------------------------
    // QWidget Demo
#if 1
    // 1. 未指定父窗口，该窗口就是独立的窗口，不受主窗口的影响
    //    需要主动调用show方法将其显示
    QWidgetDemo *subWidget = new QWidgetDemo();
    subWidget->setWindowTitle("QWidget demo");
    subWidget->show();
#else

    // 2.指定了父窗口，则该窗口就是内嵌窗口。
    // 不需要主动调用show方法，因为其父窗口显示时，会自动显示子窗口
    // 当主窗口销毁时，也会先销毁子窗口
    QWidgetDemo *subWidget = new QWidgetDemo(this);
    subWidget->show();
#endif
}


