#pragma once
#include <qobject.h>

// �Զ����ź�

class Test : public QObject
{
	Q_OBJECT
signals:
	// �����Զ�����ź�
	void TestSignal();

	// �źź���������
	// ���������������ݴ���, ˭�����źź���˭��ָ��ʵ��
	// ʵ�����ջᱻ���ݸ��ۺ���
	void TestSignal(std::string msg);
};

