#ifndef WERTUNG2DIALOG_H
#define WERTUNG2DIALOG_H

#include <QDialog>

namespace Ui {
class wertung2dialog;
}

class wertung2dialog : public QDialog
{
    Q_OBJECT

public:
    explicit wertung2dialog(QWidget *parent = nullptr);
    ~wertung2dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::wertung2dialog *ui;
};

#endif // WERTUNG2DIALOG_H
