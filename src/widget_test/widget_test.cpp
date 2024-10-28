#include "widget_test.h"
#include "winstate.h"

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
    this->setWindowFlags(Qt::WindowTitleHint  | Qt::CustomizeWindowHint);


    WinState *state = new WinState();
    state->show();

}

widget_test::~widget_test()
{}
