#include "widget.h"
#include <QApplication>
#include <opencv2/highgui.hpp>

int main(int argc, char *argv[])
{
    cv::namedWindow("opencv");
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
