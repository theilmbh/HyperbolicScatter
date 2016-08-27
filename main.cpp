#include "poincaredisk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PoincareDisk w;
    w.loadData("Test");
    w.show();

    return a.exec();
}
