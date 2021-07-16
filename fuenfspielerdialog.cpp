#include "fuenfspielerdialog.h"
#include "ui_fuenfspielerdialog.h"

FuenfSpielerDialog::FuenfSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuenfSpielerDialog)
{
    ui->setupUi(this);
}

FuenfSpielerDialog::~FuenfSpielerDialog()
{
    delete ui;
}
