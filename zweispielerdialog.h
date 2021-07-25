#ifndef ZWEISPIELERDIALOG_H
#define ZWEISPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class ZweiSpielerDialog;
}

class ZweiSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZweiSpielerDialog(QWidget *parent = nullptr);
    ~ZweiSpielerDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ZweiSpielerDialog *ui;
};

#endif // ZWEISPIELERDIALOG_H
