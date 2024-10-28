#include "widget_test.h"
#include <QtWidgets/QApplication>
#include <QThread>
#include <iostream>
#include "YThread.h"

//static QWidget *w = nullptr;
static widget_test* w = nullptr;


#if 0
// �������߳���ʹ��show�ۺ���
class Thread : public QThread
{
public:
	void run()
	{
		//w->show();
		msleep(3000);
		// ����Hide�����ź�
		w->Hide();
	}
};
#endif

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

    // ���ô��ڵ�����
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

	// 3. ���ڵ����꼰���
	// geometry()���ش��ڵľ�����Ϣ����x,y,height,width
	QRect rect = w->geometry();
	std::cout << "x: " << rect.x() << " y: " << rect.y() << " height: " << rect.height()
		<< " width: " << rect.width() << std::endl;
	// ���ô��ڵĴ�С������
	w->setGeometry(200, 100, 800, 600);
	rect = w->geometry();
	std::cout << "x: " << rect.x() << " y: " << rect.y() << " height: " << rect.height()
		<< " width: " << rect.width() << std::endl;
#endif

	// 2. demo �ٲ�ʹ�ö�ʱ��������£���ʾ������������أ�ģ�������ʱ��logo
	// ���������߳���˯�����룬Ȼ����widget��ʹ���źŲ�
	// t.start();

	//t.start(); 
	//w->show();

	/*
	widget_test w;
	// 1. ���ô��ڱ���
	w.setWindowTitle("widget");
	w.show();
	*/
	return a.exec();
}
