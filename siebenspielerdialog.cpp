#include "siebenspielerdialog.h"
#include "ui_siebenspielerdialog.h"

SiebenSpielerDialog::SiebenSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiebenSpielerDialog)
{
    ui->setupUi(this);
}

SiebenSpielerDialog::~SiebenSpielerDialog()
{
    delete ui;
}
