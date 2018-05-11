#include "grandprix.h"
#include "ui_grandprix.h"

GrandPrix::GrandPrix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GrandPrix)
{
    ui->setupUi(this);

    setWindowTitle("GrandPrix v3.0.1");
    QObject::connect(ui->controlview, SIGNAL(mapChanged(GPControl *)),
                     ui->mapview, SLOT(mapChanged(GPControl *)));

    ui->driverview->setDriverView(true);

    QObject::connect(ui->controlview,SIGNAL(carToFollow(int)),
                     ui->driverview,SLOT(setCarToFollow(int)));

    QObject::connect(ui->controlview, SIGNAL(mapChanged(GPControl *)),
                     ui->driverview, SLOT(mapChanged(GPControl *)));

    QObject::connect(ui->controlview, SIGNAL(start()),
                     ui->log, SLOT(clear()));

    QObject::connect(ui->controlview, SIGNAL(carMoved(QString)),
                     ui->log, SLOT(appendPlainText(QString)));
    QObject::connect(ui->controlview, SIGNAL(driverTimeout(QString)),
                     ui->log, SLOT(appendPlainText(QString)));
    QObject::connect(ui->controlview, SIGNAL(invalidMove(QString)),
                     ui->log, SLOT(appendPlainText(QString)));
    QObject::connect(ui->controlview, SIGNAL(syntaxError(QString)),
                     ui->log, SLOT(appendPlainText(QString)));
    QObject::connect(ui->controlview, SIGNAL(serverResponse(QString)),
                     ui->log, SLOT(appendPlainText(QString)));
}

GrandPrix::~GrandPrix()
{
    delete ui;
}
