#ifndef GPCONTROLVIEW_H
#define GPCONTROLVIEW_H

#include "gpcontrol.h"
#include <QWidget>
#include <QMessageBox>
#include "gpdriverselector.h"
#include <QVBoxLayout>

//#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <QUrl>

namespace Ui
{
class GPControlView;
}

class GPControlView : public QWidget
{
    Q_OBJECT

public:
    explicit GPControlView(QWidget *parent = 0);
    ~GPControlView();

private:
    Ui::GPControlView *ui;
    GPControl *gpControl;
    QVBoxLayout driverSelectorsLayout;
    GPDriverSelector driverSelectors[3];

    void enableControls();
    void disableControls();
    void newGPControl();
    void updateDriverInfo();
    //void sendResults(QString);

private slots:
    void on_gpMapSelector_mapSelected(const QString & mapPath);
    void gpDriverSelector_debugToggle(int car, bool debug);
    void on_runbutton_clicked();

    void on_delaySlider_valueChanged(int value);
    void gpControl_carMoved();
    void gpControl_carMovedWithBoost();
    void gpControl_end(QString);
    void gpControl_driverTimeout();
    void gpControl_invalidMove();
    void gpControl_syntaxError();

    void on_abortbutton_clicked();
    void serviceRequestFinished(QNetworkReply *reply);

    void onNextCarModeChanged(int index);
    void onFollowModeChanged(int index);

signals:
    void mapChanged(GPControl *gpControl);
    void carMoved(QString);
    void driverTimeout(QString);
    void invalidMove(QString);
    void syntaxError(QString);
    void serverResponse(QString);
    void start();

    void carToFollow(int);
};

#endif // GPCONTROLVIEW_H
