#include "widget.h"
#include <QApplication>
#include <opencv2/highgui.hpp>
#include "form1.h"

int main(int argc, char *argv[])
{
    cv::namedWindow("opencv");
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Form1 form1;
    form1.show();

    return a.exec();
}
