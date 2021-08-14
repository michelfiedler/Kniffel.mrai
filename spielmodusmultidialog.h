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

public slots:
    void chooseNewCell();

signals:
    void wrongCell();

private:
    Ui::spielmodusMultiDialog *ui;
};

#endif // SPIELMODUSMULTIDIALOG_H
