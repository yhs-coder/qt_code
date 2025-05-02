#include "winstate.h"
#include "ui_winstate.h"

WinState::WinState(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WinState)
{
    ui->setupUi(this);
}

WinState::~WinState()
{
    delete ui;
}


