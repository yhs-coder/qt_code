#include "cbasesetwidget.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

CBaseSetWidget::CBaseSetWidget(QWidget* parent) : QWidget{parent}
{
    // 设置成无边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 强制让控件使用样式表（QSS）中定义的背景样式
    setAttribute(Qt::WA_StyledBackground);

    this->setStyleSheet("background-color:rgb(51, 51, 51);color:rgb(200,200,200);");

    QLabel* pBaseSetLabel = new QLabel(this);
    pBaseSetLabel->setText("基本设置");

    QCheckBox* pCheckBoot = new QCheckBox(this);
    pCheckBoot->setText("开机启动");

    QCheckBox* pCheckDoNotDisturbMode = new QCheckBox(this);
    pCheckDoNotDisturbMode->setFixedWidth(140);
    pCheckDoNotDisturbMode->setText("开启免打扰模式");

    QLabel* p1 = new QLabel(this);
    p1->setText("?");

    QCheckBox* pCheckBosskey = new QCheckBox(this);
    pCheckBosskey->setFixedWidth(105);
    pCheckBosskey->setText("开启老板键");
    QLineEdit* pLineEdit = new QLineEdit(this);
    pLineEdit->setFixedWidth(100);
    pLineEdit->setStyleSheet("border-style:solid;border-width:1px;border-color:rgb(79,79,79);");
    QLabel* p2 = new QLabel(this);
    p2->setText("?");

    QCheckBox* pCheckNewShowMainUI = new QCheckBox(this);
    pCheckNewShowMainUI->setText("新建时显示主界面");

    QLabel* pDownloadMode = new QLabel(this);
    pDownloadMode->setText("下载模式");

    QRadioButton* pFullSpeedDownload = new QRadioButton(this);
    pFullSpeedDownload->setText("全速下载");

    QRadioButton* pSpeedLimitDownload = new QRadioButton(this);
    pSpeedLimitDownload->setText("限速下载");
    pSpeedLimitDownload->setFixedWidth(90);

    QPushButton* pBtnModify = new QPushButton(this);
    pBtnModify->setText("修改设置");
    pBtnModify->setStyleSheet("background-color:#1A1A1A;color:#5F5F5F");

    QLabel* pConfiginfo = new QLabel(this);
    pConfiginfo->setText(u8"限制时间段: 00:00-23:59 最大下载速度:不限速");

    // 整体垂直布局
    QVBoxLayout* pMainVlay = new QVBoxLayout(this);
    pMainVlay->addWidget(pBaseSetLabel);
    // 垂直布局间隔20px
    pMainVlay->addSpacing(20);

    QHBoxLayout* pHlay1 = new QHBoxLayout(this);
    pHlay1->addSpacing(35);

    QVBoxLayout* pVlay1 = new QVBoxLayout(this);
    pVlay1->addWidget(pCheckBoot);
    pVlay1->addSpacing(20);

    QHBoxLayout* pHlay2 = new QHBoxLayout(this);
    pHlay2->addWidget(pCheckDoNotDisturbMode);
    pHlay2->addWidget(p1);

    pVlay1->addLayout(pHlay2);  // 添加免打扰的水平布局
    pVlay1->addSpacing(20);

    QHBoxLayout* pHlay3 = new QHBoxLayout(this);
    pHlay3->addWidget(pCheckBosskey);
    pHlay3->addWidget(pLineEdit);
    pHlay3->addWidget(p2);

    pVlay1->addLayout(pHlay3);
    pVlay1->addSpacing(20);

    pVlay1->addWidget(pCheckNewShowMainUI);
    pVlay1->addSpacing(20);

    pVlay1->addWidget(pDownloadMode);
    pVlay1->addSpacing(20);

    QHBoxLayout* pHlay4 = new QHBoxLayout(this);  //  下载模式下面的水平布局
    pHlay4->addSpacing(30);

    QVBoxLayout* pVlay2 = new QVBoxLayout(this);

    QHBoxLayout* pHlay5 = new QHBoxLayout(this);
    pHlay5->addWidget(pFullSpeedDownload);
    pHlay5->addWidget(p2);
    pVlay2->addLayout(pHlay5);
    pVlay2->addSpacing(20);
    // 限速下载
    QHBoxLayout* pHlay6 = new QHBoxLayout(this);
    pHlay6->addWidget(pSpeedLimitDownload);
    pHlay6->addWidget(pBtnModify);
    pHlay6->addWidget(pConfiginfo);
    pHlay6->addStretch();

    pVlay2->addLayout(pHlay6);
    pHlay4->addLayout(pVlay2);

    pVlay1->addLayout(pHlay4);
    pHlay1->addLayout(pVlay1);

    // 主窗口设置为该布局方式
    pMainVlay->addLayout(pHlay1);
    pMainVlay->setContentsMargins(20, 20, 20, 20);
}
