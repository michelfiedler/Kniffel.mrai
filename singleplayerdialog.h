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

    void on_tW_SpielstandSingle_cellClicked(int row, int column);

    void on_pBwuerfeln_clicked();

    void on_pBW1_clicked();

    void on_pBW2_clicked();

    void on_pBW3_clicked();

    void on_pBW4_clicked();

    void on_pBW5_clicked();

public slots:
    void neuWaehlen();


public:
signals:
    void besetzt();


private:
    Ui::singleplayerDialog *ui;
};

#endif // SINGLEPLAYERDIALOG_H
