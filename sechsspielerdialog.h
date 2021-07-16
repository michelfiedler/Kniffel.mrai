#ifndef SECHSSPIELERDIALOG_H
#define SECHSSPIELERDIALOG_H

#include <QDialog>

namespace Ui {
class SechsSpielerDialog;
}

class SechsSpielerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SechsSpielerDialog(QWidget *parent = nullptr);
    ~SechsSpielerDialog();

private:
    Ui::SechsSpielerDialog *ui;
};

#endif // SECHSSPIELERDIALOG_H
