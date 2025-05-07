#include "widget.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

Widget::Widget(QWidget* parent) : QWidget(parent)
{
    // this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
    // 头像
    QLabel* pImageLabel = new QLabel(this);
    QPixmap pixmap(":/resources/test.jpg");
    pImageLabel->setFixedSize(150, 150);
    pImageLabel->setPixmap(pixmap);
    pImageLabel->setScaledContents(true);

    // 用户名
    QLineEdit* pUserNameLineEdit = new QLineEdit(this);
    pUserNameLineEdit->setFixedSize(300, 50);
    pUserNameLineEdit->setPlaceholderText(" QQ号码/手机/邮箱");

    QLineEdit* pPasswordLineEdit = new QLineEdit(this);
    pPasswordLineEdit->setFixedSize(300, 50);
    pPasswordLineEdit->setPlaceholderText(" 密码");
    pPasswordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton* pForgotButton = new QPushButton(this);
    pForgotButton->setText("找回密码");
    pForgotButton->setFixedWidth(80);

    QCheckBox* pRememberCheckBox = new QCheckBox(this);
    pRememberCheckBox->setText("记住密码");

    QCheckBox* pAutoLoginCheckBox = new QCheckBox(this);
    pAutoLoginCheckBox->setText("自动登录");

    QPushButton* pLoginButton = new QPushButton(this);
    pLoginButton->setFixedHeight(48);
    pLoginButton->setText("登录");

    QPushButton* pRegisterButton = new QPushButton(this);
    pRegisterButton->setFixedHeight(48);
    pRegisterButton->setText("注册账号");

    // 创建栅格布局
    QGridLayout* pGridLay = new QGridLayout(this);
    // 需要跨越3行1列 (占据3行1列 )
    // 从第0行第0列开始
    // 跨越3行(行 0-2)和1列(列 0)
    pGridLay->addWidget(pImageLabel, 0, 0, 3, 1);
    pGridLay->addWidget(pUserNameLineEdit, 0, 1, 1, 2);
    pGridLay->addWidget(pPasswordLineEdit, 1, 1, 1, 2);
    pGridLay->addWidget(pForgotButton, 2, 1, 1, 1);
    pGridLay->addWidget(pRememberCheckBox, 2, 2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    pGridLay->addWidget(pAutoLoginCheckBox, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
    pGridLay->addWidget(pLoginButton, 3, 1, 1, 2);
    pGridLay->addWidget(pRegisterButton, 4, 1, 1, 2);

    pGridLay->setHorizontalSpacing(20);
    pGridLay->setVerticalSpacing(20);

    pGridLay->setContentsMargins(30, 30, 30, 30);
}

Widget::~Widget() {}
