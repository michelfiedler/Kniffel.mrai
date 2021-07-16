#ifndef VIERSPIELERDIALOG_H
#define VIERSPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class VierSpielerDialog;
}

class VierSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VierSpielerDialog(QWidget *parent = nullptr);
    ~VierSpielerDialog();

private:
    Ui::VierSpielerDialog *ui;
};

#endif // VIERSPIELERDIALOG_H
