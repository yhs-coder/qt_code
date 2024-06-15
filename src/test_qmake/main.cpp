#include <iostream>
#include <QWidget>
#include <QApplication>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

    namedWindow("opencv");
    QApplication a(argc, argv);
    QWidget w;
    w.show();

    cout << "tets for qmake" << endl;
    a.exec();
    return 0;
}
