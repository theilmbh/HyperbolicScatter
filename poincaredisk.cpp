#include <QtWidgets>
#include <iostream>
#include <random>
#include <malloc/malloc.h>
#include <math.h>
#include <complex>

#include "poincaredisk.h"
#include "ui_poincaredisk.h"

PoincareDisk::PoincareDisk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoincareDisk)
{
    ui->setupUi(this);

    setWindowTitle(tr("Poincare Disk"));
    resize(200, 200);
}

PoincareDisk::~PoincareDisk()
{
    delete ui;
}

void PoincareDisk::loadData(char *filename)
{
    npts = 500;
    pts_real = (double *)malloc(npts*sizeof(double));
    pts_imag = (double *)malloc(npts*sizeof(double));

    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist_r(0.0, 1.0);
    std::uniform_real_distribution<double> dist_t(0, 2*3.14159);
    double r, thet;
    for (int i = 0; i < npts; i++)
    {
        r = dist_r(gen);
        thet = dist_t(gen);
        pts_real[i] = r*std::cos(thet);
        pts_imag[i] = r*std::sin(thet);
        //std::cout << pts_real[i] << " " << pts_imag[i] << std::endl;
    }

}

void PoincareDisk::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    double ptx, pty;
    int ptx_p, pty_p;

    int side = qMin(width(), height());
    int radius = (side - DISKBORDER) / 2;

    QPoint centre = QPoint(width() / 2, height() / 2);

    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QColor(255, 255, 255));
    // Draw Boundary Circle
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(centre, radius, radius);

    //Draw Points
    painter.setBrush(QColor(255, 0, 0));
    for(int pt = 0; pt < this->npts; pt++)
    {
        ptx = pts_real[pt];
        pty = pts_imag[pt];
        ptx_p = (int)std::floor(ptx*radius);
        pty_p = (int)std::floor(pty*radius);
        painter.drawEllipse(QPoint(ptx_p, pty_p) + centre, PTRAD, PTRAD);
    }
}

void PoincareDisk::mobiusTransform(double *v_d, double s)
{
    std::complex<double> v(v_d[0], v_d[1]);

    double r = std::tanh(s/2);
    for(int pt = 0; pt < this->npts; pt++)
    {
        std::complex<double> z(pts_real[pt], pts_imag[pt]);
        std::complex<double> zp;

        zp = (-1.0*r*v + z) / (-1.0*r*v*std::conj(z) + 1.0);
        pts_real[pt] = (double)std::real(zp);
        pts_imag[pt] = (double)std::imag(zp);
    }

}

void PoincareDisk::keyPressEvent(QKeyEvent *event)
{
    int the_key = event->key();
    if(the_key == Qt::Key_Left)
    {
        mobiusTransform(mhoriz_xlat, 0.1);
        xlat += 0.1;
    } else if (the_key == Qt::Key_Right) {
        mobiusTransform(mhoriz_xlat, -0.1);
        xlat -= 0.1;
    }
    if(the_key == Qt::Key_Up)
    {
        mobiusTransform(mvert_xlat, 0.1);
        ylat +=0.1;
    } else if (the_key == Qt::Key_Down) {
        mobiusTransform(mvert_xlat, -0.1);
        ylat -=0.1;
    }
    update();
}


