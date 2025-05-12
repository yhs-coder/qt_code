#include "useritem.h"

#include "ui_useritem.h"

UserItem::UserItem(QWidget *parent) : QWidget(parent), ui(new Ui::UserItem)
{
    ui->setupUi(this);

    setFixedSize(150, 150);
}

UserItem::~UserItem() { delete ui; }
