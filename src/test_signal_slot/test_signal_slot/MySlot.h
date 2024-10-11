#pragma once
#include <qobject.h>
class MySlot : public QObject
{
	Q_OBJECT
public slots:
	void eat();
};

