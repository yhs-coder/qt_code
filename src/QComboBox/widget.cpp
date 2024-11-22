#include "widget.h"
#include "ui_widget.h"


QStringList gdCityList = {"广州市", "深圳市", "珠海市", "东莞市"};
QStringList zjCityList = {"杭州市", "宁波市", "温州市", "绍兴市"};
QStringList sdCityList = {"济南市", "青岛市", "烟台市", "威海市"};
QStringList hbCityList = {"石家庄市", "保定市", "廊坊市", "衡水市"};
QStringList nmCityList = {"呼和浩特市", "包头市", "呼伦贝尔市", "赤峰市"};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    ui->leName->setText("张三");
    // 使用addItem，在组合框中添加省份
    ui->cboProvince->addItem("广东省");
    ui->cboProvince->addItem("浙江省");
    ui->cboProvince->addItem("山东省");
    ui->cboProvince->addItem("河北省");
    ui->cboProvince->addItem("内蒙古自治区");

    // 在大学第二个条目插入
    ui->cboUniversity->insertItem(1, "国防科技大学");

    // 为每个省份添加图标
    ui->cboProvince->setItemIcon(0, QIcon(":/icon/apple.ico"));
    ui->cboProvince->setItemIcon(1, QIcon(":/icon/banana.ico"));
    ui->cboProvince->setItemIcon(2, QIcon(":/icon/orange.ico"));
    ui->cboProvince->setItemIcon(3, QIcon(":/icon/peach.ico"));
    ui->cboProvince->setItemIcon(4, QIcon(":/icon/strawberry.ico"));

    // 默认选择第一项
    ui->cboProvince->setCurrentIndex(0);
    ui->cboCity->addItems(gdCityList);

    connect(ui->cboProvince, SIGNAL(currentIndexChanged(int)), this, SLOT(onCboProvinceChanged(int)));
    connect(ui->cboCity, SIGNAL(currentIndexChanged(int)), this, SLOT(onCboCityChanged(int)));
    connect(ui->cboUniversity, SIGNAL(currentIndexChanged(int)), this, SLOT(onCboUniversityChanged(int)));
    // 当文本框内容变化时，更新结果
    connect(ui->leName, &QLineEdit::textChanged, this, &Widget::onLineEditChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setResult()
{
    // 获取姓名、大学、省份、城市

    QString name = ui->leName->text();
    QString university = ui->cboUniversity->currentText();
    QString province = ui->cboProvince->currentText();
    QString city = ui->cboCity->currentText();
    ui->leResult->setText(name + "毕业于" + university + ", 来自"+ province + city);
}

void Widget::onCboUniversityChanged(int index)
{
    setResult();
}

void Widget::onCboProvinceChanged(int index)
{
    ui->cboCity->clear();
    switch(index) {
    case 0:
        ui->cboCity->addItems(gdCityList);
        break;
    case 1:
         ui->cboCity->addItems(zjCityList);
        break;
    case 2:
         ui->cboCity->addItems(sdCityList);
        break;
    case 3:
         ui->cboCity->addItems(hbCityList);
        break;
    case 4:
         ui->cboCity->addItems(nmCityList);
        break;
    default:
        break;
    }
    // 更新结果
    setResult();
}

void Widget::onCboCityChanged(int index)
{
    // 更新结果
    setResult();
}

void Widget::onLineEditChanged(QString s)
{
    // 更新结果
    setResult();
}

