#include "test_signal_slot.h"

#include <iostream>


test_signal_slot::test_signal_slot(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    // ���������ź�
    ViewSig();

	//connect(ui.testButton, SIGNAL(clicked()), this, SLOT(TestSlot()));

    connect(ui.testButton, &QPushButton::clicked, this, &QWidget::close);

    m_t = new Test;
    m_s = new MySlot;
    // ���Զ�����źźͲ�
    connect(m_t, &Test::TestSignal, m_s, &MySlot::eat);
}

test_signal_slot::~test_signal_slot()
{}

void test_signal_slot::TestSlot()
{
	std::cout << "TestSlot..." << std::endl;
}

void test_signal_slot::ViewSlot()
{
    std::cout << "ViewSlot" << std::endl;
}