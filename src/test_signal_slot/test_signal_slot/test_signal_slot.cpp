#include "test_signal_slot.h"
#include <QDebug>
#include <iostream>



test_signal_slot::test_signal_slot(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// ���������ź�
	ViewSig();

	//connect(ui.testButton, SIGNAL(clicked()), this, SLOT(TestSlot()));

	connect(ui.testButton, &QPushButton::clicked, this, &QWidget::close);

	m_t = new Test;
	m_s = new MySlot;

	// ��ʹ��connect���������źŷ�����һ���Զ����ź�
	//connect(ui.hungry, &QPushButton::clicked, m_t, &Test::TestSignal);

	// �����ť���ɲۺ��������Զ����ź�
	//connect(ui.hungry, &QPushButton::clicked, this, &test_signal_slot::HungrySlot);

	// ����ʹ��lambda���ʽд�ۺ���
	connect(ui.hungry, &QPushButton::clicked, this, [=]() {
		// �����Զ����ź�
		m_t->TestSignal();
		m_t->TestSignal("chicken");
		});


	// ���Զ�����źźͲ�
	//connect(m_t, &Test::TestSignal, m_s, &MySlot::eat);

	// һ���źſ��԰󶨶����
	//connect(m_t, &Test::TestSignal, this, &test_signal_slot::EatOther);

	// ����ź����أ�����Ҫʹ�ú���ָ���������ص��źź���
	void (Test:: * h1)() = &Test::TestSignal;
	void (Test:: * h2)(std::string) = &Test::TestSignal;
	void (MySlot:: * s1)() = &MySlot::eat;
	void (MySlot:: * s2)(std::string) = &MySlot::eat;
	connect(m_t, h1, m_s, s1);
	connect(m_t, h2, m_s, s2);

	// ʹ��Qt4�ķ�ʽ���źŲ�
	connect(m_t, SIGNAL(TestSignal()), m_s, SLOT(eat()));
	connect(m_t, SIGNAL(TestSignal(std::string)), m_s, SLOT(eat(std::string)));

	/*int a = 100, b = 200, c = 300;
	[&]() {
		//std::cout << "����һ��lambda���ʽ" << std::endl;
		//std::cout << "ʹ�����õķ�ʽ��������" << std::endl;
		//std::cout << "a + 1: " << a++ << ", b + c = " << b + c << std::endl;
		qDebug() << "����һ��lambda���ʽ";
		qDebug() << "ʹ�����õķ�ʽ��������";
		qDebug() << "a++: " << a++ << ", b + c = " << b + c;
	 }();
	qDebug() << "a = " << a;

	// ֵ�����ķ�ʽʹ���ⲿ����
	[=](int m, int n)mutable {
	//	qDebug() << "����һ��lambda���ʽ";
	//	qDebug() << "ʹ�ÿ����ķ�ʽ��������";
		qDebug() << "a++: " << a++ << ", b + c = " << b + c;
		qDebug() << "m + 1: " << m++ << ", n:  = " << n;

	 }(1, 2);
	//qDebug() << "a = " << a;
	*/

}

test_signal_slot::~test_signal_slot()
{}

void test_signal_slot::TestSlot()
{
	std::cout << "TestSlot..." << std::endl;
}

void test_signal_slot::HungrySlot()
{
	// TODO: ��������ʱ����ʾ�������л��з�������
	emit m_t->TestSignal("happy");
	// �����ź�
	emit m_t->TestSignal();
}

void test_signal_slot::EatOther()
{
	std::cout << "������տ�..." << std::endl;
}

void test_signal_slot::ViewSlot()
{
	std::cout << "ViewSlot" << std::endl;
}