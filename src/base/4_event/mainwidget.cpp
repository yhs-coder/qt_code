#include "mainwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "context_widget.h"
#include "drag_widget.h"
#include "enter_leave_widget.h"
#include "key_widget.h"
#include "paint_widget.h"
#include "press_move_release_widget.h"
#include "propagate_widget.h"
#include "timer_widget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
    initUI();
    initNav();
    initMain();
}

MainWidget::~MainWidget() {}

void MainWidget::initUI()
{
    // 整体采用水平布局
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // 左侧导航窗体
    m_navWidget             = new QWidget(this);
    QVBoxLayout* leftLayout = new QVBoxLayout(m_navWidget);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    horizontalLayout->addWidget(m_navWidget);

    // 右侧主体布局-子界面
    m_mainWidget = new QWidget(this);
    m_mainWidget->setMinimumWidth(450);
    QVBoxLayout* rightLayout = new QVBoxLayout(m_mainWidget);
    rightLayout->setSpacing(0);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    m_stackedWidget = new QStackedWidget(m_mainWidget);
    rightLayout->addWidget(m_stackedWidget);

    horizontalLayout->addWidget(m_mainWidget);
}

void MainWidget::initNav()
{
    QStringList names;
    names << "鼠标进入/离开"
          << "鼠标按下/移动/释放"
          << "键盘事件"
          << "定时器事件"
          << "拖动事件"
          << "绘图事件"
          << "右键菜单"
          << "总结：事件的传递流程";
    m_btnGroup = new QButtonGroup(this);

    // 设置样式表 - 按钮的字体大小
    m_navWidget->setStyleSheet(R"(
            QPushButton {
                font: 25px;
                text-align: left
            }
    )");
    for (int i = 0; i < names.count(); i++) {
        QPushButton* btn = new QPushButton();

        // 设置固定高度
        btn->setMinimumHeight(60);

        // 设置按钮的文字
        btn->setText(QString("%1. %2").arg(i + 1, 2, 10, QChar('0')).arg(names.at(i)));

        // 设置按钮可选中，类似复选框的功能
        btn->setCheckable(true);

        // 将按钮添加到btnGroup
        m_btnGroup->addButton(btn, i);
        // 获取当前布局（垂直），在导航栏中添加按钮控件
        m_navWidget->layout()->addWidget(btn);

        // 关联信号槽
        connect(btn, &QPushButton::clicked, this, &MainWidget::buttonClicked);
    }

    // 默认选择第一个按钮
    m_btnGroup->button(0)->click();
}

void MainWidget::initMain()
{
    // QStackedWidget::addWidget() 会把传入的 widget 的父对象设成自己，所以在 不手动 delete 的前提下不会泄漏
    m_stackedWidget->addWidget(new EnterLeaveWidget());
    m_stackedWidget->addWidget(new PressMoveReleaseWidget());
    m_stackedWidget->addWidget(new KeyWidget());
    m_stackedWidget->addWidget(new TimerWidget());
    m_stackedWidget->addWidget(new DragWidget());
    m_stackedWidget->addWidget(new PaintWidget());
    m_stackedWidget->addWidget(new ContextWidget());
    m_stackedWidget->addWidget(new PropagateWidget());
}

void MainWidget::buttonClicked()
{
    // 获取被点击按钮的id
    int id = m_btnGroup->checkedId();
    // 堆栈窗口跳转到对应界面
    m_stackedWidget->setCurrentIndex(id);
}
