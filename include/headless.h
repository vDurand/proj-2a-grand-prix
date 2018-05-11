#ifndef HEADLESS_H
#define HEADLESS

#include <QObject>
#include <QApplication>
#include "gpcontrol.h"

class Headless : public QCoreApplication
{
    Q_OBJECT

private:
    GPControl control;

public:
    Headless(int& argc, char** argv, bool* loaded);

public slots:
    void on_end(QString str);
};

#endif
