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

private:
    Ui::MultiplayerDialog *ui;
};

#endif // MULTIPLAYERDIALOG_H
