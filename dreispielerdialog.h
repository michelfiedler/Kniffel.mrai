#ifndef DREISPIELERDIALOG_H
#define DREISPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class DreiSpielerDialog;
}

class DreiSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DreiSpielerDialog(QWidget *parent = nullptr);
    ~DreiSpielerDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DreiSpielerDialog *ui;
};

#endif // DREISPIELERDIALOG_H
