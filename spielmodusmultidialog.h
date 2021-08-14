#ifndef SPIELMODUSMULTIDIALOG_H
#define SPIELMODUSMULTIDIALOG_H

#include <QDialog>

namespace Ui {
class spielmodusMultiDialog;
}

class spielmodusMultiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit spielmodusMultiDialog(QWidget *parent = nullptr);
    ~spielmodusMultiDialog();

private slots:
    void on_buttonBox_rejected();

    void on_tW_SpielstandMulti_cellClicked(int row, int column);

    void on_pBwuerfeln_clicked();

    void on_pBW1_clicked();

    void on_pBW2_clicked();

    void on_pBW3_clicked();

    void on_pBW4_clicked();

    void on_pBW5_clicked();

public slots:
    void chooseNewCell();

signals:
    void wrongCell();

private:
    Ui::spielmodusMultiDialog *ui;
};

#endif // SPIELMODUSMULTIDIALOG_H
