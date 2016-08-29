#include "poincaredisk.h"
#include "interactivehyperbolicscatterplot.h"
#include <QApplication>
#include <QtWidgets>
#include <QObject>
#include <QHBoxLayout>
#include <QSizePolicy>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InteractiveHyperbolicScatterPlot *win = new InteractiveHyperbolicScatterPlot();
    win->setWindowTitle("Hyberbolic Multidimensional Scaling Visualization");
    win->show();

    return a.exec();
}
