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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SechsSpielerDialog *ui;

public: signals:
    void tabelleFuellen6();
};

#endif // SECHSSPIELERDIALOG_H
