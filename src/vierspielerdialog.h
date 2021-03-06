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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VierSpielerDialog *ui;

public: signals:
    void tabelleFuellen4();
};

#endif // VIERSPIELERDIALOG_H
