#include "gpprogression.h"
#include "ui_gpprogression.h"

GPProgression::GPProgression(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPProgression)
{
    ui->setupUi(this);
}

GPProgression::~GPProgression()
{
    delete ui;
}
