#include "test_signal_slot.h"
#include <QDebug>
#include <iostream>



test_signal_slot::test_signal_slot(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// 主动发出信号
	ViewSig();

	//connect(ui.testButton, SIGNAL(clicked()), this, SLOT(TestSlot()));

	connect(ui.testButton, &QPushButton::clicked, this, &QWidget::close);

	m_t = new Test;
	m_s = new MySlot;

	// 可使用connect函数，让信号发生另一个自定义信号
	//connect(ui.hungry, &QPushButton::clicked, m_t, &Test::TestSignal);

	// 点击按钮，由槽函数发射自定义信号
	//connect(ui.hungry, &QPushButton::clicked, this, &test_signal_slot::HungrySlot);

	// 可以使用lambda表达式写槽函数
	connect(ui.hungry, &QPushButton::clicked, this, [=]() {
		// 发射自定义信号
		m_t->TestSignal();
		m_t->TestSignal("chicken");
		});


	// 绑定自定义的信号和槽
	//connect(m_t, &Test::TestSignal, m_s, &MySlot::eat);

	// 一个信号可以绑定多个槽
	//connect(m_t, &Test::TestSignal, this, &test_signal_slot::EatOther);

	// 如果信号重载，则需要使用函数指针区分重载的信号函数
	void (Test:: * h1)() = &Test::TestSignal;
	void (Test:: * h2)(std::string) = &Test::TestSignal;
	void (MySlot:: * s1)() = &MySlot::eat;
	void (MySlot:: * s2)(std::string) = &MySlot::eat;
	connect(m_t, h1, m_s, s1);
	connect(m_t, h2, m_s, s2);

	// 使用Qt4的方式绑定信号槽
	connect(m_t, SIGNAL(TestSignal()), m_s, SLOT(eat()));
	connect(m_t, SIGNAL(TestSignal(std::string)), m_s, SLOT(eat(std::string)));

	/*int a = 100, b = 200, c = 300;
	[&]() {
		//std::cout << "这是一个lambda表达式" << std::endl;
		//std::cout << "使用引用的方式传递数据" << std::endl;
		//std::cout << "a + 1: " << a++ << ", b + c = " << b + c << std::endl;
		qDebug() << "这是一个lambda表达式";
		qDebug() << "使用引用的方式传递数据";
		qDebug() << "a++: " << a++ << ", b + c = " << b + c;
	 }();
	qDebug() << "a = " << a;

	// 值拷贝的方式使用外部数据
	[=](int m, int n)mutable {
	//	qDebug() << "这是一个lambda表达式";
	//	qDebug() << "使用拷贝的方式传递数据";
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
	// TODO: 输入中文时会显示常量中有换行符的问题
	emit m_t->TestSignal("happy");
	// 发射信号
	emit m_t->TestSignal();
}

void test_signal_slot::EatOther()
{
	std::cout << "请你吃烧烤..." << std::endl;
}

void test_signal_slot::ViewSlot()
{
	std::cout << "ViewSlot" << std::endl;
}