#include "vierspielerdialog.h"
#include "ui_vierspielerdialog.h"

VierSpielerDialog::VierSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VierSpielerDialog)
{
    ui->setupUi(this);
}

VierSpielerDialog::~VierSpielerDialog()
{
    delete ui;
}
