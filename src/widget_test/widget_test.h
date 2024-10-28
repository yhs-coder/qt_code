#pragma once

#include <QtWidgets/QWidget>
#include "ui_widget_test.h"

class widget_test : public QWidget
{
	Q_OBJECT

public:
	widget_test(QWidget* parent = nullptr);
	~widget_test();

signals:
	void Hide();

public slots:
	void move(int x, int y) 
	{
		QWidget::move(x, y);
	}

private:
	Ui::widget_testClass ui;
};
