#ifndef GRANDPRIX_H
#define GRANDPRIX_H

#include <QMainWindow>
#include "gpcontrolview.h"
#include "gpmapview.h"

namespace Ui
{
class GrandPrix;
}

class GrandPrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit GrandPrix(QWidget *parent = 0);
    ~GrandPrix();

private:
    Ui::GrandPrix *ui;
};

#endif // GRANDPRIX_H
