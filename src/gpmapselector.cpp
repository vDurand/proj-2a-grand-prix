#include "gpmapselector.h"
#include "ui_gpmapselector.h"
#include <QtDebug>
#include <QDir>

GPMapSelector::GPMapSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPMapSelector)
{
    ui->setupUi(this);
    QDir tracks = QDir("./tracks/");
    //qWarning() << QDir::currentPath();
    //qWarning() << tracks;

    QStringList filters;
    filters << "*.txt";

    ui->listMap->addItems(tracks.entryList(filters, QDir::Files | QDir::Readable, QDir::Name));

    mapSel = QString();
}

GPMapSelector::~GPMapSelector()
{
    delete ui;
}

void GPMapSelector::enabledSelectionChange(bool state)
{
    ui->listMap->setEnabled(state);
}

void GPMapSelector::on_listMap_itemSelectionChanged()
{
    QListWidgetItem *item = ui->listMap->currentItem();
    if (item) {
        mapSel = "./tracks/" + item->text();
        emit mapSelected(mapSel);
    }
}

QString GPMapSelector::getMapSelected()
{
    return mapSel;
}
