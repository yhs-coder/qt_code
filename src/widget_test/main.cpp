#include "widget_test.h"
#include <QtWidgets/QApplication>
#include <QThread>
#include <iostream>
#include "YThread.h"

//static QWidget *w = nullptr;
static widget_test* w = nullptr;


#if 0
// 测试在线程中使用show槽函数
class Thread : public QThread
{
public:
	void run()
	{
		//w->show();
		msleep(3000);
		// 发射Hide隐藏信号
		w->Hide();
	}
};
#endif

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

    // 设置窗口的类型
    widget_test w;
    w.setWindowTitle("customize");
    w.show();

#if 0
    w = new widget_test();

	w->setWindowTitle("widget");

	YThread t;
	QObject::connect(&t, &YThread::Move, w, &widget_test::move);

	w->show();
	t.start();

	// 3. 窗口的坐标及宽高
	// geometry()返回窗口的矩形信息，即x,y,height,width
	QRect rect = w->geometry();
	std::cout << "x: " << rect.x() << " y: " << rect.y() << " height: " << rect.height()
		<< " width: " << rect.width() << std::endl;
	// 设置窗口的大小及坐标
	w->setGeometry(200, 100, 800, 600);
	rect = w->geometry();
	std::cout << "x: " << rect.x() << " y: " << rect.y() << " height: " << rect.height()
		<< " width: " << rect.width() << std::endl;
#endif

	// 2. demo 再不使用定时器的情况下，显示窗口三秒后隐藏，模拟软件打开时的logo
	// 方案：在线程中睡眠三秒，然后在widget中使用信号槽
	// t.start();

	//t.start(); 
	//w->show();

	/*
	widget_test w;
	// 1. 设置窗口标题
	w.setWindowTitle("widget");
	w.show();
	*/
	return a.exec();
}
