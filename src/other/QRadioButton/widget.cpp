#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置第二组的默认显示
    ui->rbMale2->setChecked(true);
    ui->rbDoctor2->setChecked(true);

    // 设置第三组的默认显示
    ui->rbMale3->setChecked(true);
    ui->rbDoctor3->setChecked(true);

    // 设置第四组的默认显示
    ui->rbMale4->setChecked(true);
    ui->rbDoctor4->setChecked(true);

    // 将男女单选按钮加入到组
    mBtnGroupGender = new QButtonGroup(this);
    mBtnGroupGender->addButton(ui->rbMale4, 0);
    mBtnGroupGender->addButton(ui->rbFemale4, 1);

    // 将不同学历加入到一组
    mBtnGroupEdu = new QButtonGroup(this);
    mBtnGroupEdu->addButton(ui->rbDoctor4, 10);
    mBtnGroupEdu->addButton(ui->rbMaster4, 11);
    mBtnGroupEdu->addButton(ui->rbBachelor4, 12);
    mBtnGroupEdu->addButton(ui->rbOther4, 13);

    connect(ui->rbMale4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbFemale4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbDoctor4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbMaster4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbBachelor4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);
    connect(ui->rbOther4, &QRadioButton::clicked, this, &Widget::onRadioButtonClicked);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnGetSelection_clicked()
{
    QString result{};

    // 获取男女的选中
    if (ui->rbMale3->isChecked()) {
        result += ui->rbMale3->text();
    } else {
        result += ui->rbFemale3->text();
    }

    // 获取博士/硕士/本科/其它的显示
    if (ui->rbDoctor3->isChecked()) {
        result += ui->rbDoctor3->text();
    } else if (ui->rbMaster3->isChecked()) {
        result += ui->rbMaster3->text();
    } else if (ui->rbBachelor3->isChecked()) {
        result += ui->rbBachelor3->text();
    } else if (ui->rbOther3->isChecked()) {
        result += ui->rbOther3->text();
    }
    // 显示到文本框
    ui->leResult->setText(result);
}

void Widget::onRadioButtonClicked()
{
    QString s;

    int checkedGenderId = mBtnGroupGender->checkedId();
    if(checkedGenderId == 0) {
        s += "男";
    } else if(checkedGenderId == 1) {
        s += "女";
    }

    int checkedEduId = mBtnGroupEdu->checkedId();
    if(checkedEduId == 10) {
        s += "博士";
    } else if(checkedEduId == 11) {
        s += "硕士";
    } else if(checkedEduId == 12) {
        s += "本科";
    } else if(checkedEduId == 13) {
        s += "其他";
    }

    ui->leSelect->setText(s);
}


void Widget::on_rbMale4_toggled(bool checked)
{
    qDebug()<< "rbMale4 state changed: " << checked;
}

