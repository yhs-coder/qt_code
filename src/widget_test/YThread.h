#pragma once
#include <QThread>
class YThread : public QThread
{
	Q_OBJECT
public:
	void run()
	{
		for (int x = 0; x < 1000; x++)
		{
			Move(x, x);
			msleep(10);
		}
	}

	~YThread();
signals:
	void Move(int x, int y);

};

