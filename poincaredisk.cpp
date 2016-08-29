#include <QtWidgets>
#include <iostream>
#include <fstream>
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
    setFocusPolicy(Qt::StrongFocus);
}

PoincareDisk::~PoincareDisk()
{
    delete ui;
}

void PoincareDisk::loadData()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Dataset"), "/Users/brad/");
    do_loadData(fileName);
    update();
}

void PoincareDisk::do_loadData_random(QString fileName)
{
    npts = 5000;
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

void PoincareDisk::do_loadData(QString fileName)
{
    std::streampos size;
    std::ifstream dataFile(fileName.toStdString(), std::ios::binary | std::ios::in | std::ios::ate);
    if (dataFile.is_open())
    {
        size = dataFile.tellg();
        char *memblock = new char[size];
        dataFile.seekg(0, std::ios::beg);
        dataFile.read(memblock, size);
        dataFile.close();
        npts = (int)(size/(2*sizeof(double)));
        std::cout << "Npts: " << npts << std::endl;
        double *dmemblock = (double *)memblock;
        std::cout << "Copying data into real and imag registers\n";

        pts_real = new double[npts];
        pts_imag = new double[npts];
        for (int i = 0; i<npts; i++)
        {
            pts_real[i] = dmemblock[2*i];
            pts_imag[i] = dmemblock[2*i + 1];
        }
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

void PoincareDisk::rotate(double theta)
{

    std::complex<double> phase(std::cos(theta), std::sin(theta));
    for(int pt = 0; pt < this->npts; pt++)
    {
        std::complex<double> z(pts_real[pt], pts_imag[pt]);
        std::complex<double> zp;
        zp = phase*z;
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
        update_x(0.1);
    } else if (the_key == Qt::Key_Right) {
        mobiusTransform(mhoriz_xlat, -0.1);
        update_x(-0.1);
    }
    if(the_key == Qt::Key_Up)
    {
        mobiusTransform(mvert_xlat, 0.1);
        update_y(0.1);
    } else if (the_key == Qt::Key_Down) {
        mobiusTransform(mvert_xlat, -0.1);
        update_y(-0.1);
    }

    switch(the_key)
    {
        case Qt::Key_R:
            rotate(-0.01);
            break;
        case Qt::Key_L:
            rotate(0.01);
            break;
    }

    update();
}

void PoincareDisk::update_x(double delta)
{
    x_lat += delta;
    emit x_translate(x_lat);
}

void PoincareDisk::update_y(double delta)
{
    y_lat += delta;
    emit y_translate(y_lat);
}

