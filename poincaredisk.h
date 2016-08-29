#ifndef POINCAREDISK_H
#define POINCAREDISK_H

#include <QWidget>
#include <complex>

#define DISKBORDER 10
#define PTRAD 2

namespace Ui {
class PoincareDisk;
}

class PoincareDisk : public QWidget
{
    Q_OBJECT

public:
    explicit PoincareDisk(QWidget *parent = 0);
    ~PoincareDisk();

    void do_loadData(char *filename);

public slots:
    void loadData();

signals:
    void x_translate(double newx);
    void y_translate(double newy);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::PoincareDisk *ui;
    double *pts_real;
    double *pts_imag;
    int npts;
    bool gridOn;
    double x_lat = 0;
    double y_lat = 0;

    double horiz_xlat[2] = {1.0, 0.0};
    double vert_xlat[2] = {0.0, 1.0};
    double mhoriz_xlat[2] = {-1.0, 0.0};
    double mvert_xlat[2] = {0.0, -1.0};
    void mobiusTransform(double *v_d, double s);
    void rotate(double theta);
    void update_x(double delta);
    void update_y(double delta);
};

#endif // POINCAREDISK_H
