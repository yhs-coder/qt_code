#include "test_signal_slot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_signal_slot w;
    w.show();
    return a.exec();
}
