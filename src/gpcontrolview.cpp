#include <stdlib.h>
#include <QtDebug>
#include <QCryptographicHash>

#include "finishdialog.h"
#include "gpcontrol.h"
#include "gpcontrolview.h"
#include "ui_gpcontrolview.h"

GPControlView::GPControlView(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GPControlView),
  gpControl(NULL)
{

  ui->setupUi(this);
  QObject::connect(ui->gpMapSelector, SIGNAL(mapSelected(QString)),
                   this, SLOT(on_gpMapSelector_mapSelected(QString)));

  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectorsLayout.addWidget(driverSelectors + noCar);
    driverSelectors[noCar].setNoCar(noCar);
    QObject::connect(&driverSelectors[noCar], SIGNAL(debugToggle(int, bool)),
                     this, SLOT(gpDriverSelector_debugToggle(int, bool)));
  }
  ui->driverGroupBox->setLayout(&driverSelectorsLayout);

  ui->cbFollow->addItem("All",GPControl::FollowAll);
  ui->cbFollow->addItem("Car 1",GPControl::FollowCar1);
  ui->cbFollow->addItem("Car 2",GPControl::FollowCar2);
  ui->cbFollow->addItem("Car 3",GPControl::FollowCar3);
  ui->cbFollow->setCurrentIndex(0);
  connect(ui->cbFollow,SIGNAL(currentIndexChanged(int)),
          this,SLOT(onFollowModeChanged(int)));

  ui->cbNextCarMode->addItem("Random",RANDOM);
  ui->cbNextCarMode->addItem("Determinist",DETERMINIST);
  ui->cbNextCarMode->addItem("Sequential",SEQUENTIAL);
  ui->cbNextCarMode->setCurrentIndex(0);
  connect(ui->cbNextCarMode,SIGNAL(currentIndexChanged(int)),
          this,SLOT(onNextCarModeChanged(int)));

  newGPControl();
  enableControls();
}

GPControlView::~GPControlView()
{
  delete ui;
}

void GPControlView::disableControls()
{
  ui->runbutton->setEnabled(false);
  ui->abortbutton->setEnabled(true);
  ui->gpMapSelector->enabledSelectionChange(false);
  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectors[noCar].setEnabled(false);
  }
}

void GPControlView::enableControls()
{
  ui->abortbutton->setEnabled(false);
  ui->gpMapSelector->enabledSelectionChange(true);
  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectors[noCar].setEnabled(true);
  }
  QString map = ui->gpMapSelector->getMapSelected();
  ui->runbutton->setEnabled(!map.isEmpty());
}

void GPControlView::newGPControl()
{
  if (gpControl) {
    delete gpControl;
  }

  gpControl = new GPControl(this);
  gpControl->setDelay(ui->delaySlider->value());
  gpControl->setNextCarMode(static_cast<NextCarMode>(ui->cbNextCarMode->currentData().toInt()));

  QString map = ui->gpMapSelector->getMapSelected();
  if (!map.isEmpty()) {
    gpControl->setMap(map);
  }

  for (int noCar = 0; noCar < 3; noCar++) {
    gpControl->setCarDebug(noCar, driverSelectors[noCar].debugIsChecked());
  }
}

void GPControlView::on_gpMapSelector_mapSelected(const QString &mapPath)
{
  if (gpControl->setMap(mapPath)) {
    emit mapChanged(gpControl);
    enableControls();
  } else {
    QMessageBox msg(this);
    msg.setText(tr("Invalid map, please choose another one."));
    msg.exec();
  }
}

void GPControlView::gpDriverSelector_debugToggle(int car, bool debug)
{
  gpControl->setCarDebug(car, debug);
}

void GPControlView::on_runbutton_clicked()
{
  emit start();
  for (int noCar = 0; noCar < gpControl->getNbCars(); noCar++) {
    gpControl->setDriverPath(noCar, driverSelectors[noCar].getDriverPath());
  }
  disableControls();
  QObject::connect(gpControl, SIGNAL(end(QString)),
                   this, SLOT(gpControl_end(QString)));
  QObject::connect(gpControl, SIGNAL(carMoved()),
                   this, SLOT(gpControl_carMoved()));
  QObject::connect(gpControl, SIGNAL(carMovedWithBoost()),
                   this, SLOT(gpControl_carMovedWithBoost()));
  QObject::connect(gpControl, SIGNAL(invalidMove()),
                   this, SLOT(gpControl_invalidMove()));
  QObject::connect(gpControl, SIGNAL(syntaxError()),
                   this, SLOT(gpControl_syntaxError()));
  QObject::connect(gpControl, SIGNAL(driverTimeout()),
                   this, SLOT(gpControl_driverTimeout()));

  gpControl->nextMove();
}

void GPControlView::on_abortbutton_clicked()
{
  gpControl->disconnect(SIGNAL(end(QString)));
  gpControl->disconnect(SIGNAL(carMoved()));
  gpControl->disconnect(SIGNAL(carMovedWithBoost()));
  gpControl->disconnect(SIGNAL(invalidMove()));
  gpControl->disconnect(SIGNAL(syntaxError()));
  gpControl->disconnect(SIGNAL(driverTimeout()));

  newGPControl();
  enableControls();
}

void GPControlView::updateDriverInfo()
{
  for (int noCar = 0; noCar < gpControl->getNbCars(); noCar++) {
    int nbMoves = gpControl->getNbMoves(noCar);
    int nbFailures = gpControl->getNbFailures(noCar);
    int carburant = gpControl->getCarburant(noCar);
    driverSelectors[noCar].setInfo(nbMoves, nbFailures, carburant);
  }
}

void GPControlView::gpControl_carMoved()
{
  emit mapChanged(gpControl);
  int curCar = gpControl->getCurrentCar();
  QString res = tr("Driver %1: move to (%2,%3) new velocity (%4,%5), %6 boosts left, gas left %7 (%8 used)")
      .arg(curCar + 1)
      .arg(gpControl->getPosCarX(curCar))
      .arg(gpControl->getPosCarY(curCar))
      .arg(gpControl->getVelCarX(curCar))
      .arg(gpControl->getVelCarY(curCar))
      .arg(gpControl->getBoost(curCar))
      .arg(gpControl->getCarburant(curCar))
      .arg(gpControl->gasolineAtStart()-gpControl->getCarburant(curCar));
  emit carMoved(res);
  updateDriverInfo();
}

void GPControlView::gpControl_carMovedWithBoost()
{
  emit mapChanged(gpControl);
  int curCar = gpControl->getCurrentCar();
  QString res = tr("Driver %1 boost: move to (%2,%3) new velocity is (%4,%5), %6 boosts left, gas left %7 (%8 used)")
      .arg(curCar + 1)
      .arg(gpControl->getPosCarX(curCar))
      .arg(gpControl->getPosCarY(curCar))
      .arg(gpControl->getVelCarX(curCar))
      .arg(gpControl->getVelCarY(curCar))
      .arg(gpControl->getBoost(curCar))
      .arg(gpControl->getCarburant(curCar))
      .arg(gpControl->gasolineAtStart()-gpControl->getCarburant(curCar));
  emit carMoved(res);
  updateDriverInfo();
}

void GPControlView::gpControl_invalidMove()
{
  int curCar = gpControl->getCurrentCar();
  emit invalidMove(tr("Driver %1: invalid move %2 carburant").arg(gpControl->getCurrentCar() + 1).arg(gpControl->getCarburant(curCar)));
  updateDriverInfo();
}

void GPControlView::gpControl_syntaxError()
{
  emit invalidMove(tr("Driver %1: syntax error").arg(gpControl->getCurrentCar() + 1));
}

void GPControlView::gpControl_driverTimeout()
{
  emit driverTimeout(tr("Driver %1: time out.").arg(gpControl->getCurrentCar() + 1));
}


void GPControlView::on_delaySlider_valueChanged(int value)
{
  gpControl->setDelay(value);
}

void GPControlView::gpControl_end(QString results)
{
  FinnishDialog *msg = new FinnishDialog(this);
  msg->setResults(results);
  msg->setWindowTitle(tr("Finnish!"));
  msg->setModal(true);
  msg->exec();
  delete msg;

  on_abortbutton_clicked();

}


//void GPControlView::sendResults(QString pseudo)
//{
//    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
//    connect(networkManager, SIGNAL(finished(QNetworkReply*)),
//            this, SLOT(serviceRequestFinished(QNetworkReply*)));
//    QNetworkRequest request(QUrl("http://jgosme.perso.info.unicaen.fr/GrandPrix/results.cgi"));
//    request.setRawHeader("Host", "jgosme.perso.info.unicaen.fr");

//    QByteArray postData;
//    postData.append("GP:1.0\n");
//    postData.append(QString("pseudo:%1\n").arg(pseudo));
//    postData.append(QString("nbCars:%1\n").arg(gpControl->getNbCars()));
//    postData.append(QString("map:%1\n").arg(ui->gpMapSelector->getMapSelected()));
//    postData.append("mapHash:");
//    QCryptographicHash hash(QCryptographicHash::Md5);
//    hash.addData(gpControl->mapData());
//    postData.append(hash.result().toHex());
//    postData.append("\n");
//    hash.reset();

//    for (int i = 0; i < gpControl->getNbCars(); i++) {
//        postData.append(QString("driver%1:").arg(i));
//        postData.append(driverSelectors[i].getDriverFileName());
//        postData.append("\n");

//        postData.append(QString("driver%1Hash:").arg(i));
//        QFile driverFile(driverSelectors[i].getDriverPath());
//        driverFile.open(QIODevice::ReadOnly | QIODevice::Unbuffered);
//        hash.addData(driverFile.readAll());
//        postData.append(hash.result().toHex());
//        postData.append("\n");
//        hash.reset();
//        driverFile.close();

//        postData.append(QString("nbMoves%1:%2\n").arg(i).arg(gpControl->getNbMoves(i)));
//    }

//    //qWarning() << QString("Send post request (size=%1)").arg(postData.size());
//    //qWarning() <<postData;
//    networkManager->post(request, postData);

//}

void GPControlView::serviceRequestFinished(QNetworkReply *reply)
{
  emit serverResponse(tr("Server response: %1").arg(QString(reply->readAll()).trimmed()));
}

void GPControlView::onNextCarModeChanged(int index)
{
  gpControl->setNextCarMode(static_cast<NextCarMode>(ui->cbNextCarMode->itemData(index).toInt()));
}

void GPControlView::onFollowModeChanged(int index)
{
  switch (index) {
  case GPControl::FollowAll:
  emit carToFollow(-1);
  break;
  case GPControl::FollowCar1:
    emit carToFollow(0);
  break;
  case GPControl::FollowCar2:
    emit carToFollow(1);
  break;
  case GPControl::FollowCar3:
    emit carToFollow(2);
  break;
  }
}

