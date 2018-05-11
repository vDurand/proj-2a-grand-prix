#include "gpmapview.h"
#include "ui_gpmapview.h"
#include <assert.h>
#include <QtCore/qmath.h>
#include <QMouseEvent>

GPMapView::GPMapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPMapView),
    driverView(false),
    zoom(1.),
    normal(":/res/normal.png"),
    sand(":/res/sand.png"),
    goal(":/res/goal.png"),
    out(":/res/out.png"),
    car1(":/res/car1.png"),
    car2(":/res/car2.png"),
    car3(":/res/car3.png"),
    available1(":/res/available1.png"),
    available2(":/res/available2.png"),
    available3(":/res/available3.png"),
    current(":/res/current.png"),
    carToFollow(-1)
{
    ui->setupUi(this);

    gpControl = NULL;

}

GPMapView::~GPMapView()
{
    delete ui;
}


void GPMapView::mapChanged(GPControl *gpControl)
{
    this->gpControl = gpControl;
    this->update();
}


void GPMapView::setDriverView(bool driverView)
{
  this->driverView = driverView;
}

void GPMapView::setCarToFollow(int nCar)
{
  carToFollow = nCar;
}

void GPMapView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    assert(event == event);
    if (this->gpControl == NULL || this->gpControl->getNbCars() == 0) {
        return;
    }


    int sizeX = this->gpControl->getSizeX();
    int sizeY = this->gpControl->getSizeY();

    float tileWidth = 0.0;
    float tileHeight = 0.0;

    int minX = 0;
    int minY = 0;

    int maxX = 0;
    int maxY = 0;

    int offsetY = 32;
    int offsetX = 32;

    int sizeXWidget = 0;
    int sizeYWidget = 0;

    int curCar = gpControl->getCurrentCar();
    if ( carToFollow != -1 ) {
      curCar = carToFollow;
    }
    int curCarX = gpControl->getPosCarX(curCar);
    int curCarY = gpControl->getPosCarY(curCar);

    sizeXWidget = this->width();
    sizeYWidget = this->height();

    float radius;
    if (driverView) {
        radius = 4 * zoom;
    } else {
        radius = std::max(sizeY, sizeX) * zoom;
    }
    if (sizeXWidget >= sizeYWidget) {
        minX = curCarX - (int)(sizeXWidget / sizeYWidget * radius);
        maxX = curCarX + (int)(sizeXWidget / sizeYWidget * radius);

        minY = curCarY - radius;
        maxY = curCarY + radius;
    } else {
        minX = curCarX - radius;
        maxX = curCarX + radius;

        minY = curCarY - (int)(sizeYWidget / sizeXWidget * radius);
        maxY = curCarY + (int)(sizeYWidget / sizeXWidget * radius);
    }
    if (!driverView) {
        minX = std::max(0, minX);
        minY = std::max(0, minY);
        maxX = std::min(sizeX, maxX);
        maxY = std::min(sizeY, maxY);
    }

    tileWidth = (float)(this->size().width() - offsetX) / (maxX - minX);
    tileHeight = (float)(this->size().height() - offsetY) / (maxY - minY);

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            int type = gpControl->getTile(x, y);
            QImage *img;
            switch (type) {
                case GPControl::NORMAL:
                    img = &normal;
                    break;
                case GPControl::OUT:
                    img = &out;
                    break;
                case GPControl::GOAL:
                    img = &goal;
                    break;
                case GPControl::SAND:
                    img = &sand;
                    break;
                default:
                    img = &out;
            }


            painter.drawImage(QRectF(offsetX + tileWidth * (x - minX), offsetY + tileHeight * (y - minY), tileWidth + 0.01, tileHeight + 0.01),
                              *img,
                              QRectF(0, 0, 36, 36));
            if ((y - minY) == 0 && (driverView || x % 5 == 0)) {
                painter.drawText(QRectF(offsetX + tileWidth * (x - minX - 1), 0, tileWidth * 3 + 0.01, offsetY),
                                 QString("%1").arg(x),
                                 QTextOption(Qt::AlignCenter));
            }
            if ((x - minX) == 0 && (driverView || y % 5 == 0)) {
                painter.drawText(QRectF(0, offsetY + tileHeight * (y - minY - 1), offsetX, tileHeight * 3 + 0.01),
                                 QString("%1").arg(y),
                                 QTextOption(Qt::AlignCenter));
            }
        }
    }



    for (int noCar = 0; noCar < this->gpControl->getNbCars(); noCar++) {
        QImage *img = NULL;
        QRectF rectf;
        qreal angle;
        switch (gpControl->getPosDepart(noCar)) {
            case 1:
                img = &car1;
                break;
            case 2:
                img = &car2;
                break;
            case 3:
                img = &car3;
                break;
                //default:


                //color=Qt::magenta;
                //qWarning("unknown car type '%i'", noCar);

        }

        // Display of availables positions and current car indicator
        if (noCar == gpControl->getCurrentCar()) {
            painter.drawImage(QRectF(offsetX + tileWidth * (curCarX - minX), offsetY + tileHeight * (curCarY - minY), tileWidth, tileHeight),
                              current,
                              QRectF(0, 0, 36, 36));

            if (gpControl->getCarDebug(noCar)) {
                QImage *img_available = NULL;
                if (noCar == 0)      img_available = &available1;
                else if (noCar == 1) img_available = &available2;
                else if (noCar == 2) img_available = &available3;


                QSet<QPair<int, int> > available = gpControl->availableMoves(noCar);
                QSet<QPair<int, int> >::iterator i;
                for (i = available.begin(); i != available.end(); ++i) {
                    painter.drawImage(QRectF(offsetX + tileWidth  * (gpControl->getPosCarX(noCar) + gpControl->getVelCarX(noCar) + i->first - minX),
                                             offsetY + tileHeight * (gpControl->getPosCarY(noCar) + gpControl->getVelCarY(noCar) + i->second - minY),
                                             tileWidth,
                                             tileHeight),
                                      *img_available,
                                      QRectF(0, 0, 36, 36));

                }

            }
        }

        // Display of the cars
        if (img != NULL) {
            angle = qAtan2(gpControl->getVelCarX(noCar), gpControl->getVelCarY(noCar)); // Radius between -Pi et Pi
            angle = angle * 180 / M_PI + 90;
            painter.translate(offsetX + tileWidth * (gpControl->getPosCarX(noCar) - minX) + tileWidth * 0.5, offsetY + tileHeight * (gpControl->getPosCarY(noCar) - minY) + tileHeight * 0.5);  // On déplace le système de coordonnées au centre de l'emplacement que l'on veut
            painter.rotate(-angle);
            rectf = QRectF(- tileWidth * 0.5, - tileHeight * 0.5, tileWidth, tileHeight);   // Destination rectangle with rotation
            painter.drawImage(rectf, *img, QRectF(0, 0, 36, 36));
            painter.resetTransform();   // Rotation and translation reset
        }

        // Display of the trajectory of the cars with lines
        for (int i = 1; i < gpControl->getNbPositions(noCar); i++) {
            QPen pen;
            qreal widthBrush = qAbs((tileWidth + tileHeight) / 20);
            QColor color = gpControl->getColor(noCar);

            pen.setStyle(Qt::DotLine);
            pen.setWidthF(widthBrush);
            color.setAlpha(100);
            pen.setBrush(color);
            pen.setCapStyle(Qt::SquareCap);

            painter.setPen(pen);
            painter.drawLine(offsetX + tileWidth * (gpControl->getOldPosCarX(noCar, i - 1) - minX) + tileWidth * 0.5, offsetY + tileHeight * (gpControl->getOldPosCarY(noCar, i - 1) - minY) + tileHeight * 0.5, offsetX + tileWidth * (gpControl->getOldPosCarX(noCar, i) - minX) + tileWidth * 0.5, offsetY + tileHeight * (gpControl->getOldPosCarY(noCar, i) - minY) + tileHeight * 0.5);
        }

        // Display of the old positions of the cars with circles
        for (int i = 0; i < (gpControl->getNbPositions(noCar) - 1); i++) {
            int boostUsed = 0, j = 0;

            while (!boostUsed && j < gpControl->getNbBoostUsed(noCar)) { // Looking for a boost usage at the current position
                boostUsed = (i == gpControl->getIndexBoostUsed(noCar, j));
                j++;
            }

            QPen pen;
            qreal widthCircle = (tileWidth + tileHeight) / 5 * (1 + boostUsed);

            pen = painter.pen();

            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);

            painter.drawEllipse(offsetX + tileWidth * (gpControl->getOldPosCarX(noCar, i) - minX) + tileWidth / 2 - widthCircle / 2, offsetY + tileHeight * (gpControl->getOldPosCarY(noCar, i) - minY) + tileHeight / 2 - widthCircle / 2, widthCircle, widthCircle);

        }
    }
}

void GPMapView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
    } else if (event->button() == Qt::RightButton) {
        zoom = 1.;
    }
    this->update();
}
void GPMapView::wheelEvent(QWheelEvent* event)
{
    float delta;
    if (event->delta() < 0) {
        delta = 1.2;
    } else {
        delta = 0.8;
    }
    zoom *= delta;
    this->update();
}

