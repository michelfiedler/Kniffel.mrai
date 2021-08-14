#include "spielmodusmultidialog.h"
#include "ui_spielmodusmultidialog.h"

spielmodusMultiDialog::spielmodusMultiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spielmodusMultiDialog)
{
    ui->setupUi(this);
}

spielmodusMultiDialog::~spielmodusMultiDialog()
{
    delete ui;
}
