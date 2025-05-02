#include "widget.h"

#include <QApplication>
#include <opencv2/highgui.hpp>
#include "form1.h"
#include "form2.h"

int main(int argc, char *argv[])
{
    cv::namedWindow("opencv");
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Form1 f1;
    f1.show();
    Form2 f2;
    f2.show();

    return a.exec();
}
