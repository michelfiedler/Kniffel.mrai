#ifndef FUENFSPIELERDIALOG_H
#define FUENFSPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class FuenfSpielerDialog;
}

class FuenfSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FuenfSpielerDialog(QWidget *parent = nullptr);
    ~FuenfSpielerDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FuenfSpielerDialog *ui;

public: signals:
    void tabelleFuellen5();
};

#endif // FUENFSPIELERDIALOG_H
