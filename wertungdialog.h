#ifndef WERTUNGDIALOG_H
#define WERTUNGDIALOG_H

#include <QDialog>

namespace Ui {
class wertungDialog;
}

class wertungDialog : public QDialog
{
    Q_OBJECT

public:
    explicit wertungDialog(QWidget *parent = nullptr);
    ~wertungDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::wertungDialog *ui;
};

#endif // WERTUNGDIALOG_H
