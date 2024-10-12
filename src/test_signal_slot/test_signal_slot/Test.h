#pragma once
#include <qobject.h>

// 自定义信号

class Test : public QObject
{
	Q_OBJECT
signals:
	// 测试自定义的信号
	void TestSignal();

	// 信号函数可重载
	// 参数的作用是数据传递, 谁调用信号函数谁就指定实参
	// 实参最终会被传递给槽函数
	void TestSignal(std::string msg);
};

