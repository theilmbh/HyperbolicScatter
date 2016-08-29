#include "interactivehyperbolicscatterplot.h"
#include "poincaredisk.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

InteractiveHyperbolicScatterPlot::InteractiveHyperbolicScatterPlot(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout(this);
    QHBoxLayout *hbox2 = new QHBoxLayout();

    QLCDNumber *x = new QLCDNumber(this);
    QLCDNumber *y = new QLCDNumber(this);

    QPushButton *load = new QPushButton("Load Data", this);
    PoincareDisk *plot = new PoincareDisk(this);

    QLabel *xlab = new QLabel("<font face=\"verdana\"><h2>X</h2></font>");
    QLabel *ylab = new QLabel("<font face=\"verdana\"><h2>Y</h2");

    x->setMinimumHeight(100);
    y->setMinimumHeight(100);

    connect(plot, SIGNAL(x_translate(double)), x, SLOT(display(double)));
    connect(plot, SIGNAL(y_translate(double)), y, SLOT(display(double)));
    connect(load, SIGNAL(pressed()), plot, SLOT(loadData()));

    load->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    hbox2->addWidget(load);
    vbox->setSpacing(3);
    vbox->addWidget(xlab);
    vbox->addWidget(x);
    vbox->addWidget(ylab);
    vbox->addWidget(y);
    vbox->addStretch(1);
    vbox->addLayout(hbox2);

    hbox->addWidget(createPlotBox(plot));
    hbox->addSpacing(15);
    hbox->addLayout(vbox);

    setLayout(hbox);
}

QGroupBox *InteractiveHyperbolicScatterPlot::createPlotBox(PoincareDisk *plot)
{
    QGroupBox *plotBox = new QGroupBox(tr("Poincare Disk"));
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(plot);
    plotBox->setLayout(vbox);
    return plotBox;
}
