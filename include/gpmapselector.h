#ifndef GPMAPSELECTOR_H
#define GPMAPSELECTOR_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui
{
class GPMapSelector;
}

class GPMapSelector : public QWidget
{
    Q_OBJECT

private :
    QString mapSel;

public:
    explicit GPMapSelector(QWidget *parent = 0);
    ~GPMapSelector();
    QString getMapSelected();

private slots:
    void on_listMap_itemSelectionChanged();

private:
    Ui::GPMapSelector *ui;

signals:
    void mapSelected(QString mapPath);

public slots:
    void enabledSelectionChange(bool state);
};

#endif // GPMAPSELECTOR_H
