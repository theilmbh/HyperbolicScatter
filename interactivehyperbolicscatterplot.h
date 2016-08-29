#ifndef INTERACTIVEHYPERBOLICSCATTERPLOT_H
#define INTERACTIVEHYPERBOLICSCATTERPLOT_H

#include "poincaredisk.h"
#include <QWidget>
#include <QGroupBox>

class InteractiveHyperbolicScatterPlot : public QWidget
{
    Q_OBJECT
public:
    explicit InteractiveHyperbolicScatterPlot(QWidget *parent = 0);

signals:

public slots:

private:
    QGroupBox *createPlotBox(PoincareDisk *plot);
};

#endif // INTERACTIVEHYPERBOLICSCATTERPLOT_H
