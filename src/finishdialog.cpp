#include "finishdialog.h"
#include "ui_finishdialog.h"
#include <QGridLayout>
#include <QFont>

FinnishDialog::FinnishDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinnishDialog)
{
    ui->setupUi(this);
}

FinnishDialog::~FinnishDialog()
{
    delete ui;
}

void FinnishDialog::setResults(QString results)
{
  QGridLayout * layout = dynamic_cast<QGridLayout*>(ui->table->layout());
  if ( !layout ) return;
  QFont font;
  font.setPointSize(12);
  QStringList lines = results.split('\n');
  int l = 1;
  foreach (QString line, lines) {
    QStringList cells = line.split('\t');
    for (int c = 0; c < cells.size(); ++c) {
      QLabel * label = new QLabel(cells[c],ui->table);
      if ( c == 0 || c > 1 ) {
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
      } else {
        label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      }
      label->setFont(font);
      layout->addWidget(label,l,c);
    }
    ++l;
  }
  // ui->results->setText(results);
}
