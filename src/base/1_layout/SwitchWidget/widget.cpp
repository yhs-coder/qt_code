#include "widget.h"

#include <QDebug>
#include <QLayout>
#include <QLayoutItem>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("布局切换与重构");

    // 初始化界面
    initWidget();

    // 窗口大小
    this->resize(QSize(800, 500));

    // 设置菜单策略
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
}

Widget::~Widget()
{
    if (!m_videoLabelList.isEmpty()) {
        for (int i = 0; i < 9; i++) {
            delete m_videoLabelList[i];
            // qDebug() << "删除第" << i << "个标签";
        }
    }
}

void Widget::initWidget()
{
    initMenu();

    // 将图片存入标签列表中
    for (int i = 0; i < 9; i++) {
        QLabel* label = new QLabel();
        label->setParent(nullptr);

        // %1 表示第一个占位符
        label->setStyleSheet(QString("QLabel{background-image:url(:/resources/%1.png); \
        border:1px solid gray; \
        background-position:center; \
        background-repeat:no-repeat; \
        }")
                                 .arg(QString::number(i + 1)));

        m_videoLabelList.append(label);
    }

    // 默认展示一张图
    switchLayout(VideoLayoutType::OneVideo);
}

void Widget::contextMenuEvent(QContextMenuEvent* event)
{
    // 在鼠标点击位置弹出菜单窗口
    m_switchMenu->exec(QCursor::pos());
}

void Widget::switchLayout(VideoLayoutType type)
{
    QLayout* layout = this->layout();

    // 清空布局内的所有元素

    if (layout) {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            // setParent为NULL,防止删除之后界面不消失
            if (child->widget()) {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete layout;
    }

    switch (type) {
        // 一分屏
        case OneVideo: {
            // 创建栅格布局
            QGridLayout* gLayout = new QGridLayout(this);
            gLayout->addWidget(m_videoLabelList[0]);
            gLayout->setMargin(0);
        } break;

        // 四分屏
        case FourVideo: {
            QGridLayout* gLayout = new QGridLayout(this);
            // 设置栅格之间没间隙
            gLayout->setSpacing(0);
            gLayout->setMargin(0);

            for (int i = 0; i < 4; i++) {
                // 四分屏，每行两张图片

                gLayout->addWidget(m_videoLabelList[i], i / 2, i % 2);
            }
        } break;

        // 五分屏
        case FiveVideo: {
            // 注释这种写法有bug,为五分屏切换成一分屏时布局没有销毁，或者留有一张图片没销毁

            // // 仅顶层布局设置this为父对象
            // QVBoxLayout* pVLay = new QVBoxLayout(this);
            // pVLay->setSpacing(0);

            // // 子布局不设置父对象
            // // 如果设置this为父对象，会出现 "QLayout：尝试将QLayout添加到已有布局的Widget中" 错误
            // QHBoxLayout* pHTopLay = new QHBoxLayout();
            // pHTopLay->setSpacing(0);

            // for (int i = 0; i < 3; i++) {
            //     pHTopLay->addWidget(m_videoLabelList[i]);
            // }

            // QHBoxLayout* pHBottomLay = new QHBoxLayout();
            // pHBottomLay->setSpacing(0);
            // for (int i = 3; i < 5; i++) {
            //     pHBottomLay->addWidget(m_videoLabelList[i]);
            // }
            // // 通过addLayout添加子布局
            // pVLay->addLayout(pHTopLay);
            // pVLay->addLayout(pHBottomLay);

            QGridLayout* gLayout = new QGridLayout(this);
            gLayout->setSpacing(0);
            gLayout->setMargin(0);
            gLayout->addWidget(m_videoLabelList[0], 0, 0);  // 0行0列
            gLayout->addWidget(m_videoLabelList[1], 0, 1);  // 0行1列
            gLayout->addWidget(m_videoLabelList[2], 0, 2);  // 0行2列
            // setColumnStretch,控制列的宽度比例
            gLayout->setColumnStretch(0, 2);  // 等宽
            gLayout->setColumnStretch(1, 2);
            gLayout->setColumnStretch(2, 2);
            // 第二行：两控件填充满
            gLayout->addWidget(m_videoLabelList[3], 1, 0, 1, 1);  // 1行0列，占2列
            gLayout->addWidget(m_videoLabelList[4], 1, 1, 1, 2);  // 1行2列，占1列

        } break;

        // 六分屏
        case SixVideo: {
            QGridLayout* gLayout = new QGridLayout(this);
            gLayout->addWidget(m_videoLabelList[0], 0, 0, 2, 2);
            gLayout->addWidget(m_videoLabelList[1], 0, 2, 1, 1);
            gLayout->addWidget(m_videoLabelList[2], 1, 2, 1, 1);
            gLayout->addWidget(m_videoLabelList[3], 2, 0, 1, 1);
            gLayout->addWidget(m_videoLabelList[4], 2, 1);
            gLayout->addWidget(m_videoLabelList[5], 2, 2);
            gLayout->setSpacing(0);
            gLayout->setMargin(0);
        } break;

        // 九分屏
        case NineVideo: {
            QGridLayout* gLayout = new QGridLayout(this);
            gLayout->setSpacing(0);
            gLayout->setMargin(0);

            for (int i = 0; i < 9; i++) {
                gLayout->addWidget(m_videoLabelList[i], i / 3, i % 3);
            }
        } break;

        default:
            break;
    }
}

void Widget::initMenu()
{
    m_switchMenu = new QMenu(this);
    m_switchMenu->addAction("一分屏");
    m_switchMenu->addAction("四分屏");
    m_switchMenu->addAction("五分屏");
    m_switchMenu->addAction("六分屏");
    m_switchMenu->addAction("九分屏");

    m_strTypeMap["一分屏"] = VideoLayoutType::OneVideo;
    m_strTypeMap["四分屏"] = VideoLayoutType::FourVideo;
    m_strTypeMap["五分屏"] = VideoLayoutType::FiveVideo;
    m_strTypeMap["六分屏"] = VideoLayoutType::SixVideo;
    m_strTypeMap["九分屏"] = VideoLayoutType::NineVideo;

    connect(m_switchMenu, &QMenu::triggered, this, [=](QAction* action) {
        QString         strText = action->text();
        VideoLayoutType type    = VideoLayoutType(m_strTypeMap[strText]);
        switchLayout(type);
    });
}
