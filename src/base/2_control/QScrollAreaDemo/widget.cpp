#include "widget.h"

#include <QHBoxLayout>
#include <QScrollBar>
#include <string>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    setFixedSize(150 + 1000 + 30 + 15, 900);
    // this->setStyleSheet("background-color:rgb(26, 26, 26)");
    this->setStyleSheet("background:#2A2A2A");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

    // 创建列边框
    m_pListWidget = new QListWidget(this);
    m_pListWidget->setFixedWidth(150);
    m_pListWidget->setFrameShape(QFrame::NoFrame);
    m_pListWidget->setFocusPolicy(Qt::NoFocus);

    m_textList << "基本设置" << "云盘设置" << "下载设置" << "接管设置" << "任务管理" << "提醒" << "悬浮窗";

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
        /* padding-left: 42px;        文字左缩进微调 */
    }

    QListWidget::item:!active:selected {
        /* 窗口失活时的选中状态 */
        color: rgba(61, 139, 255, 0.7);  /* 半透明蓝色 */
    }
    )";

    m_pListWidget->setStyleSheet(QString::fromStdString(lw_qss));

    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setFixedWidth(1000 + 30);
    m_pScrollArea->setFrameShape(QFrame::NoFrame);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    std::string verticalbar_qss = R"(
        QScrollBar{width:16px;background:rgb(26, 26, 26);margin:0px, 0px, 0px, 0px;}
        QScrollBar::handle:vertical{width:8px;background:rgba(162, 163, 165, 100%);border-radius:4px;min-height:40;}
              QScrollBar::handle:vertical:hover{width:8px;background:rgba(115,118,118, 100%);border-radius:4px;min-height:40;}
              QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgb(26, 26, 26);border-radius:4px;}
              QScrollBar::top-arrow:vertical,QScrollBar::bottom-arrow:vertical{border: none;background: none;color: none;}
              QScrollBar::add-line:vertical{border:none;background:none;}
              QScrollBar::sub-line:vertical{border:none;background:none;}
    )";

    m_pScrollArea->verticalScrollBar()->setStyleSheet(QString::fromStdString(verticalbar_qss));

    QWidget*     widget = new QWidget;
    QVBoxLayout* pVLay  = new QVBoxLayout(widget);

    m_pBaseSetWidget = new CBaseSetWidget;
    m_vecWidget.push_back(m_pBaseSetWidget);

    m_pYunpanSetWidget = new QWidget;
    m_pYunpanSetWidget->setStyleSheet("background-image:url(:/resources/YunPanSet.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pYunpanSetWidget->setFixedSize(1000, 478);
    m_vecWidget.push_back(m_pYunpanSetWidget);

    m_pDownloadWidget = new QWidget;
    m_pDownloadWidget->setStyleSheet("background-image:url(:/resources/XiaZai.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pDownloadWidget->setFixedSize(1000, 337);
    m_vecWidget.push_back(m_pDownloadWidget);

    m_pJieguanWidget = new QWidget;
    m_pJieguanWidget->setStyleSheet("background-image:url(:/resources/JieGuanSet.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pJieguanWidget->setFixedSize(1000, 340);
    m_vecWidget.push_back(m_pJieguanWidget);

    m_pRenwuWidget = new QWidget;
    m_pRenwuWidget->setStyleSheet("background-image:url(:/resources/RenwuGuanli.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pRenwuWidget->setFixedSize(1000, 413);
    m_vecWidget.push_back(m_pRenwuWidget);

    m_pTixingWidget = new QWidget;
    m_pTixingWidget->setStyleSheet("background-image:url(:/resources/TiXing.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pTixingWidget->setFixedSize(1000, 728);
    m_vecWidget.push_back(m_pTixingWidget);

    m_pXuanfuWidget = new QWidget;
    m_pXuanfuWidget->setStyleSheet("background-image:url(:/resources/XuanFuChuang.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
    m_pXuanfuWidget->setFixedSize(1000, 206);
    m_vecWidget.push_back(m_pXuanfuWidget);

    for (auto w : m_vecWidget) {
        pVLay->addWidget(w);
        pVLay->addSpacing(15);
    }

    pVLay->setContentsMargins(0, 5, 0, 5);

    m_pScrollArea->setWidget(widget);

    QHBoxLayout* hlay = new QHBoxLayout(this);
    hlay->addWidget(m_pListWidget);
    hlay->setSpacing(0);
    hlay->addWidget(m_pScrollArea);

    connect(m_pListWidget, &QListWidget::itemClicked, this, &Widget::slotItemClicked);

    connect(m_pScrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &Widget::slotValueChanged);
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

    delete m_pYunpanSetWidget;
    delete m_pDownloadWidget;
    delete m_pJieguanWidget;
    delete m_pRenwuWidget;
    delete m_pTixingWidget;
    delete m_pXuanfuWidget;
}

void Widget::slotItemClicked(QListWidgetItem* item)
{
    signFlag         = true;
    QString itemText = item->text();
    QPoint  widgetPos;

    int size = m_textList.size();
    for (int i = 0; i < size; i++) {
        if (itemText == m_textList[i]) {
            widgetPos = m_vecWidget[i]->pos();
        }
    }

    m_pScrollArea->verticalScrollBar()->setValue(widgetPos.y());
}

void Widget::slotValueChanged(int value)
{
    if (!signFlag) {
        int itemSize = m_vecWidget.size();
        for (int i = 0; i < itemSize; i++) {
            if (!m_vecWidget[i]->visibleRegion().isEmpty()) {
                m_pListWidget->item(i)->setSelected(true);
                return;
            } else {
                m_pListWidget->item(i)->setSelected(false);
            }
        }
    }
    signFlag = false;
}
