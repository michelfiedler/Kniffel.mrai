#include "zweispielerdialog.h"
#include "ui_zweispielerdialog.h"

ZweiSpielerDialog::ZweiSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZweiSpielerDialog)
{
    ui->setupUi(this);
}

ZweiSpielerDialog::~ZweiSpielerDialog()
{
    delete ui;
}
