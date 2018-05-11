#ifndef GPPROGRESSION_H
#define GPPROGRESSION_H

#include <QWidget>

namespace Ui
{
class GPProgression;
}

class GPProgression : public QWidget
{
    Q_OBJECT

public:
    explicit GPProgression(QWidget *parent = 0);
    ~GPProgression();

private:
    Ui::GPProgression *ui;
};

#endif // GPPROGRESSION_H
