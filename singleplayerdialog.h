#ifndef SINGLEPLAYERDIALOG_H
#define SINGLEPLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class singleplayerDialog;
}

class singleplayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit singleplayerDialog(QWidget *parent = nullptr);
    ~singleplayerDialog();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::singleplayerDialog *ui;
};

#endif // SINGLEPLAYERDIALOG_H
