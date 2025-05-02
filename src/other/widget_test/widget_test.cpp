#include "widget_test.h"
#include "winstate.h"
#include "qwidgetdemo.h"

widget_test::widget_test(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(this, &widget_test::Hide, this, &QWidget::hide);

    // ȥ������߿�ͱ������������ޱ߿򴰿�
    // this->setWindowFlags(Qt::FramelessWindowHint);

    // ���ô��ڵı�־
    // ȡ���رհ�ť��ʹ�䲻����
    // this->setWindowFlag(Qt::WindowCloseButtonHint, false);

    // ȡ����С����ť��ʹ�䲻����
    // this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);

    // ȡ����С����ť��ʹ�䲻����
    // this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    // ��ǩ��������ȥ�����а�ť
    // this->setWindowFlags(Qt::WindowTitleHint  | Qt::CustomizeWindowHint);


    WinState *state = new WinState();
    state->show();

    //------------------------------------------------------------------
    // QWidget Demo
#if 1
    // 1. δָ�������ڣ��ô��ھ��Ƕ����Ĵ��ڣ����������ڵ�Ӱ��
    //    ��Ҫ��������show����������ʾ
    QWidgetDemo *subWidget = new QWidgetDemo();
    subWidget->setWindowTitle("QWidget demo");
    subWidget->show();
#else

    // 2.ָ���˸����ڣ���ô��ھ�����Ƕ���ڡ�
    // ����Ҫ��������show��������Ϊ�丸������ʾʱ�����Զ���ʾ�Ӵ���
    // ������������ʱ��Ҳ���������Ӵ���
    QWidgetDemo *subWidget = new QWidgetDemo(this);
    subWidget->show();
#endif
}


