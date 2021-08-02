#ifndef WERTUNG2DIALOG_H
#define WERTUNG2DIALOG_H

#include <QDialog>

namespace Ui {
class wertung2Dialog;
}

class wertung2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit wertung2Dialog(QWidget *parent = nullptr);
    ~wertung2Dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::wertung2Dialog *ui;
};

#endif // WERTUNG2DIALOG_H
