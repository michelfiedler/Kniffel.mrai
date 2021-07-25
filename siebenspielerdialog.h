#ifndef SIEBENSPIELERDIALOG_H
#define SIEBENSPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class SiebenSpielerDialog;
}

class SiebenSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SiebenSpielerDialog(QWidget *parent = nullptr);
    ~SiebenSpielerDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SiebenSpielerDialog *ui;
};

#endif // SIEBENSPIELERDIALOG_H
