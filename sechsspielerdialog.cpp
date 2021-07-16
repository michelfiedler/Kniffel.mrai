#include "sechsspielerdialog.h"
#include "ui_sechsspielerdialog.h"

SechsSpielerDialog::SechsSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SechsSpielerDialog)
{
    ui->setupUi(this);
}

SechsSpielerDialog::~SechsSpielerDialog()
{
    delete ui;
}
