#ifndef MULTIPLAYERDIALOG_H
#define MULTIPLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class MultiplayerDialog;
}

class MultiplayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MultiplayerDialog(QWidget *parent = nullptr);
    ~MultiplayerDialog();

public slots:
    void fillNameTable();

private slots:
    void on_pushButton_clicked();

    void on_pBNamenEintragen_clicked();

private:
    Ui::MultiplayerDialog *ui;
};

#endif // MULTIPLAYERDIALOG_H
