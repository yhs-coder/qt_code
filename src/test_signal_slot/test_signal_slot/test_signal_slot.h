#pragma once

#include <QtWidgets/QWidget>
#include "ui_test_signal_slot.h"
#include "MySlot.h"
#include "Test.h"

class test_signal_slot : public QWidget
{
    Q_OBJECT

public:
    test_signal_slot(QWidget *parent = nullptr);
    ~test_signal_slot();

signals:
    void ViewSig();

public slots:
    void ViewSlot();
    void TestSlot();
    void HungrySlot();
    void EatOther();
private:
    Ui::test_signal_slotClass ui;
    Test* m_t;
    MySlot* m_s;
};
