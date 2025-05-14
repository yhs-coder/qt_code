#include "widget.h"

#include <QHBoxLayout>
#include <QScrollBar>
#include <string>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* pHLay = new QHBoxLayout(this);

    setFixedSize(150 + 1000 + 30 + 15, 900);
    // this->setStyleSheet("background-color:rgb(26, 26, 26)");
    this->setStyleSheet("background:#2A2A2A");

    // 创建列边框
    m_pListWidget = new QListWidget(this);
    m_pListWidget->setFixedWidth(150);
    m_pListWidget->setFrameShape(QFrame::NoFrame);
    m_pListWidget->setFocusPolicy(Qt::NoFocus);

    m_textList << "首页" << "基本设置" << "云盘设置" << "下载设置" << "接管设置" << "任务管理" << "提醒" << "悬浮窗" << "高级设置";

    m_pListWidget->addItems(m_textList);

    // std::string lw_qss = R"(
    //     QListWidget
    //     {
    //         /*border:1px solid gray;   ?????:????????*/
    //         background:rgb(26, 26, 26);   /*???????*/
    //         color:rgb(200, 200, 200);     /*?????????????*/
    //         font-size:15px;
    //         border-radius:1px;
    //     }

    //     QListWidget::item
    //     {
    //         height:40px;
    //         padding-left:10px; /*?????????left???????*/
    //     }

    //     QListWidget::item:!active
    //     {
    //         background:rgb(26, 26, 26);
    //         margin:5px 20px 1px 20px;   /*????????, ????item??ListWidget?????*/
    //     }

    //     QListWidget::item:hover
    //     {
    //         background:rgb(56, 56, 56);
    //         padding-left:30px;
    //     }

    //     QListWidget::item:selected
    //     {
    //         border-radius:15px;
    //         background:lightblue;
    //     }

    //     /*?????????????????????????*/
    //     QListWidget::item:selected:!active
    //     {
    //         background:rgb(51,51,51);
    //         color:#3F85FF;
    //     })";

    std::string lw_qss = R"(
    QListWidget {
        /* 主列表样式 */
        background: #2A2A2A;  /* 深灰底色 */
        border: none;         /* 无边框 */
        outline: 0;           /* 去除焦点虚线框 */
        font-family: "Microsoft YaHei";  /* 微软雅黑字体 */
        font-size: 18px;      /* 标准字号 */
        color: #CACACA;       /* 浅灰文字 */
        padding: 8px 0;       /* 上下内边距 */
    }

    QListWidget::item {
        /* 默认项样式 */
        height: 40px;         /* 项高度 */
        padding-left: 5px;   /* 文字缩进（配合图标布局） */
        margin: 2px 12px;     /* 项外边距 */
        border-radius: 4px;   /* 圆角 */
        border: none;         /* 无边框 */
    }

    QListWidget::item:hover {
        /* 悬停状态 */
        background: #373737;  /* 深灰悬停背景 */
        color: #FFFFFF;       /* 纯白文字 */
    }

    QListWidget::item:selected {
        /* 选中状态 */
        background: #373737;       /* 深灰背景 */
        color: #3D8BFF;           /* 迅雷标志蓝 */
        border-left: 5px solid #3D8BFF;  /* 左侧指示条 */
        padding-left: 42px;       /* 文字左缩进微调 */
    }

    QListWidget::item:!active:selected {
        /* 窗口失活时的选中状态 */
        color: rgba(61, 139, 255, 0.7);  /* 半透明蓝色 */
    }
    )";

    m_pListWidget->setStyleSheet(QString::fromStdString(lw_qss));

    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setFixedWidth(1400 + 30);
    m_pScrollArea->setFrameShape(QFrame::NoFrame);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    pHLay->addWidget(m_pListWidget);
    pHLay->addWidget(m_pScrollArea);

    QWidget*     widget = new QWidget;
    QVBoxLayout* pVLay  = new QVBoxLayout(widget);

    m_pBaseSetWidget = new CBaseSetWidget;
    pVLay->addWidget(m_pBaseSetWidget);
    widget->setLayout(pVLay);

    m_pScrollArea->setWidget(widget);
}

Widget::~Widget()
{
    if (m_pListWidget) {
        delete m_pListWidget;
    }

    if (m_pScrollArea) {
        delete m_pScrollArea;
    }

    if (m_pBaseSetWidget) {
        delete m_pBaseSetWidget;
    }
}
