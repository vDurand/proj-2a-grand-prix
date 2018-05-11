#ifndef GPMAPVIEW_H
#define GPMAPVIEW_H

#include <QWidget>
#include "gpcontrol.h"

#include <QPainter>
#include <QColor>
#include <QRect>
#include <QtDebug>

static QColor const COL_TRACK("black");
static QColor const COL_OUT_TRACK("white");
static QColor const COL_GOAL("gray");
static QColor const COL_DRIVER1("red");
static QColor const COL_DRIVER2("green");
static QColor const COL_DRIVER3("blue");


namespace Ui
{
class GPMapView;
}

class GPMapView : public QWidget
{
    Q_OBJECT

public:
    explicit GPMapView(QWidget *parent = 0);
    ~GPMapView();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void setDriverView(bool driverView);


private:
    Ui::GPMapView *ui;
    GPControl *gpControl;
    bool driverView;
    float zoom;

    QImage normal;
    QImage sand;
    QImage goal;
    QImage out;
    QImage car1;
    QImage car2;
    QImage car3;
    QImage available1;
    QImage available2;
    QImage available3;
    QImage current;

    int carToFollow;

public slots:
    void mapChanged(GPControl *gpControl);
    void setCarToFollow(int nCar);

};

#endif // GPMAPVIEW_H
