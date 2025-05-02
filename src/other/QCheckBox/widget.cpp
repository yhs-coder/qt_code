#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->cbApple, &QCheckBox::stateChanged, this, &Widget::onStateChanged);
    connect(ui->cbPeach, &QCheckBox::stateChanged, this, &Widget::onStateChanged);
    connect(ui->cbPear, &QCheckBox::stateChanged, this, &Widget::onStateChanged);
    connect(ui->cbOrange, &QCheckBox::stateChanged, this, &Widget::onStateChanged);
    connect(ui->cbBanana, &QCheckBox::stateChanged, this, &Widget::onStateChanged);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onStateChanged()
{
    QString s{};
    // 获取复选按钮的选中状态
    int appleChecked = ui->cbApple->isChecked();
    int peachChecked = ui->cbPeach->isChecked();
    int pearChecked = ui->cbPear->isChecked();
    int orangeChecked = ui->cbOrange->isChecked();
    int bananaChecked = ui->cbBanana->isChecked();

    if (appleChecked && peachChecked && pearChecked && orangeChecked && bananaChecked) {
        // 复选按钮全部选中,设置全选按钮为QCheck
        ui->cbAll->setCheckState(Qt::Checked);
    }  else if (!(appleChecked || peachChecked || pearChecked || orangeChecked || bananaChecked)) {
        // 全部未选中
        ui->cbAll->setCheckState(Qt::Unchecked);
    } else {
        // 部分选中
        ui->cbAll->setCheckState(Qt::PartiallyChecked);
    }

    if (appleChecked) {
        s += ui->cbApple->text() += " ";
    }
    if(pearChecked) {
        s += ui->cbPear->text() += " ";
    }
    if(peachChecked) {
        s += ui->cbPeach->text() += " ";
    }
    if(orangeChecked) {
        s += ui->cbOrange->text() += " ";
    }
    if(bananaChecked) {
        s += ui->cbBanana->text() += " ";
    }
    ui->leResult->setText(s);
}

void Widget::on_cbAll_clicked()
{
    // 将“全选”按钮的三态设置为false
    // 也就是在鼠标点击时，只允许在checked和unchecked之间切换，不允许出现半选状态
    ui->cbAll->setTristate(false);

    Qt::CheckState state = ui->cbAll->checkState();

    if(state == Qt::Checked) {
        ui->cbApple->setChecked(true);
        ui->cbPear->setChecked(true);
        ui->cbPeach->setChecked(true);
        ui->cbOrange->setChecked(true);
        ui->cbBanana->setChecked(true);
    }
    if (state == Qt::Unchecked){
        ui->cbApple->setChecked(false);
        ui->cbPear->setChecked(false);
        ui->cbPeach->setChecked(false);
        ui->cbOrange->setChecked(false);
        ui->cbBanana->setChecked(false);
    }
}
