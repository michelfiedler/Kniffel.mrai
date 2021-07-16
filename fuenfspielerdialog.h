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

private:
    Ui::FuenfSpielerDialog *ui;
};

#endif // FUENFSPIELERDIALOG_H
