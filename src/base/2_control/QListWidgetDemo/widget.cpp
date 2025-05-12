#include "widget.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QMessageBox>

#include "./ui_widget.h"
#include "useritem.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initTabWidget();

    QListWidgetItem* pItem1 = new QListWidgetItem(QIcon(":/resources/kits.png"), "Kits");
    QListWidgetItem* pItem2 = new QListWidgetItem(QIcon(":/resources/env.png"), "环境");
    QListWidgetItem* pItem3 = new QListWidgetItem(QIcon(":/resources/editor.png"), "编辑器");
    QListWidgetItem* pItem4 = new QListWidgetItem(QIcon(":/resources/vim.png"), "FakeVim");
    QListWidgetItem* pItem5 = new QListWidgetItem(QIcon(":/resources/help.png"), "帮助");
    QListWidgetItem* pItem6 = new QListWidgetItem;

    ui->listWidget->addItem(pItem1);
    ui->listWidget->addItem(pItem2);
    ui->listWidget->addItem(pItem3);
    ui->listWidget->addItem(pItem4);
    ui->listWidget->addItem(pItem5);
    ui->listWidget->addItem(pItem6);

    UserItem* pUserItem = new UserItem(this);
    ui->listWidget->setItemWidget(pItem6, pUserItem);

    initRightMenu();

    // 在列表框中，右键点击列表项，弹出菜单
    // 设置菜单策略，必须设置，不然无法显示菜单
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接信号槽
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, &Widget::on_PopupRightMenu);
}

Widget::~Widget()
{
    delete ui;
    delete m_subWidget;
    delete m_pMainVLayout;
    delete m_pListWidget;
}

void Widget::on_PopupRightMenu(const QPoint& pos)
{
    // 检验点击处是否为列表项
    QListWidgetItem* pItem = ui->listWidget->itemAt(pos);
    if (!pItem) {
        return;
    }
    // 展示菜单
    m_pRightMenu->exec(QCursor::pos());
}

void Widget::initRightMenu()
{
    m_pRightMenu = new QMenu(this);

    QAction* pAc1 = new QAction("动作1", this);
    QAction* pAc2 = new QAction("动作2", this);
    QAction* pAc3 = new QAction("动作3", this);
    QAction* pAc4 = new QAction("删除", this);

    m_pRightMenu->addAction(pAc1);
    m_pRightMenu->addAction(pAc2);
    m_pRightMenu->addAction(pAc3);
    m_pRightMenu->addAction(pAc4);

    connect(pAc1, &QAction::triggered, [=] { QMessageBox::information(this, "title", "ac1"); });
    // 点击删除选项时，删除对应的列表项
    connect(pAc4, &QAction::triggered, this, [=] {
        // 获取当前点击的列表项
        QListWidgetItem* item = ui->listWidget->currentItem();
        ui->listWidget->removeItemWidget(item);
        // 从列表小部件中删除的项目将不由Qt管理,需要手动把删除返回的列表项
        delete item;

        // 第二种删除方法
        // int              r    = ui->listWidget->row(item);
        // QListWidgetItem* temp = ui->listWidget->takeItem(r);
        // // 需要手动把删除返回的列表项
        // delete item;
    });
}

void Widget::initTabWidget()
{
    QWidget* subWidget = new QWidget();
    subWidget->resize(600 + 60 + 25, 600);

    m_pMainVLayout = new QVBoxLayout();
    m_pListWidget  = new QListWidget();
    // 设置列表框显示为图标模式
    m_pListWidget->setViewMode(QListView::IconMode);
    // 屏蔽水平滑动条
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 垂直滑动条需要时才显示
    m_pListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    int vScrollBarWidth = 10;

    QString qssLW = QString(
                        "QScrollBar{width:%1px;background:rgba(255, 255, 255,100%);margin:0px, 0px, 0px, 0px;}\
              QScrollBar::handle:vertical{width:2px;background:rgba(162, 163, 165, 100%);border-radius:4px;min-height:60;}\
              QScrollBar::handle:vertical:hover{width:2px;background:rgba(115,118,118, 100%);border-radius:4px;min-height:60;}\
              QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(255, 255, 255, 100%);border-radius:4px;}\
              QScrollBar::top-arrow:vertical,QScrollBar::bottom-arrow:vertical{border: none;background: none;color: none;}\
              QScrollBar::add-line:vertical{border:none;background:none;}\
              QScrollBar::sub-line:vertical{border:none;background:none;}\
              QListWidget{background-color:rgb(124,100,200);border:none;} \
              QListWidget::item{  \
              background:rgb(10,160,220);  \
              margin-left:20px;  \
              margin-right:20px; \
              margin-top:10px; \
              } \
    ")
                        .arg(QString::number(vScrollBarWidth));

    m_pListWidget->setStyleSheet(qssLW);
    // 180包括margin-left的值
    // 如果QListWidget::item没有写margin-right:20px，增加竖直滑动条和最后一列的间隙为margin-left的一半即可，这样看着美观
    // 如果QListWidget::item写了margin-right:20px, vScrollBarWidth + 1即可
    m_pListWidget->setFixedWidth(180 * 3 + vScrollBarWidth + 1);

    for (int i = 0; i < 15; i++) {
        //:/ch212_listwidget_03/resources/env.png
        QIcon            icon(":/resources/env.png");
        QString          name  = QString("用户%1").arg(QString::number(i));
        QListWidgetItem* pItem = new QListWidgetItem(icon, name);
        pItem->setSizeHint(QSize(180, 180));
        m_pListWidget->addItem(pItem);
    }

    m_pMainVLayout->addWidget(m_pListWidget);
    subWidget->setLayout(m_pMainVLayout);

    // 选项卡窗口控件
    ui->tabWidget->insertTab(2, subWidget, "列表框");
}
