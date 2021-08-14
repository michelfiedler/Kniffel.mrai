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

private:
    Ui::spielmodusMultiDialog *ui;
};

#endif // SPIELMODUSMULTIDIALOG_H
