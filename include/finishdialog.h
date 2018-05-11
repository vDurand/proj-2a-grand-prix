#ifndef FINNISHDIALOG_H
#define FINNISHDIALOG_H

#include <QDialog>

namespace Ui
{
class FinnishDialog;
}

class FinnishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinnishDialog(QWidget *parent = 0);
    ~FinnishDialog();

    void setResults(QString results);
private:
    Ui::FinnishDialog *ui;
};

#endif // FINNISHDIALOG_H
