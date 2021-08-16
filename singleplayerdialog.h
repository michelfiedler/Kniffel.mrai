#ifndef SINGLEPLAYERDIALOG_H
#define SINGLEPLAYERDIALOG_H

#include <QDialog>

#include "wertungdialog.h"
#include "wertung2dialog.h"

namespace Ui {
class singleplayerDialog;
}

class singleplayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit singleplayerDialog(QWidget *parent = nullptr);
    ~singleplayerDialog();
    void refreshTable();
    void refreshEndTabelle();

private slots:
    void on_buttonBox_rejected();

    void on_tW_SpielstandSingle_cellClicked(int row, int column);

    void on_pBwuerfeln_clicked();

    void on_pBW1_clicked();

    void on_pBW2_clicked();

    void on_pBW3_clicked();

    void on_pBW4_clicked();

    void on_pBW5_clicked();

    void on_nameSpeichern_clicked();

public slots:
    void neuWaehlen();
    void KIZug();
    void wertung();
    void wertung2();

public:
signals:
    void besetzt();
    void KIistdran();
    void SiegDu();
    void SiegKI();


private:
    Ui::singleplayerDialog *ui;
};

#endif // SINGLEPLAYERDIALOG_H
