#include "dreispielerdialog.h"
#include "ui_dreispielerdialog.h"

DreiSpielerDialog::DreiSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DreiSpielerDialog)
{
    ui->setupUi(this);
}

DreiSpielerDialog::~DreiSpielerDialog()
{
    delete ui;
}
