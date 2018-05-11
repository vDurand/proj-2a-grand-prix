#include "gpdriverselector.h"
#include "ui_gpdriverselector.h"
#include <QDir>

GPDriverSelector::GPDriverSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPDriverSelector)
{
    ui->setupUi(this);
    this->noCar = 0;

    QDir drivers = QDir("./drivers/");
    QStringList list = drivers.entryList(QDir::Files | QDir::Readable | QDir::Executable, QDir::Name);
    ui->comboBox->addItems(list);
}

void GPDriverSelector::setNoCar(int noCar)
{
    this->noCar = noCar;
    //if(noCar!=0){
    //    ui->comboBox->addItem(tr("<None>"));
    //}

    ui->label->setText(tr("Driver %1:").arg(noCar + 1));
    QString color;
    switch (noCar) {
        case 0:
            color = "red";
            break;
        case 1:
            color = "green";
            break;
        case 2:
            color = "blue";
            break;
    }
    ui->label->setStyleSheet("QLabel { color : " + color + "; }");
}

void GPDriverSelector::setEnabled(bool enabled)
{
    ui->comboBox->setEnabled(enabled);
}

QString GPDriverSelector::getDriverPath()
{
    return "./drivers/" + ui->comboBox->currentText();
}

QString GPDriverSelector::getDriverFileName()
{
    return ui->comboBox->currentText();
}

void GPDriverSelector::setInfo(int nbMoves, int nbFailures, int carburant)
{
    ui->info->setText(QString("%1 coups %3 carb (%2 fail) ").arg(nbMoves).arg(nbFailures).arg(carburant));
}

bool GPDriverSelector::debugIsChecked()
{
    return ui->debug->isChecked();
}

void GPDriverSelector::on_debug_toggled(bool toggle)
{
    emit debugToggle(noCar, toggle);
}

GPDriverSelector::~GPDriverSelector()
{
    delete ui;
}
