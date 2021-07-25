#include "dreispielerdialog.h"
#include "ui_dreispielerdialog.h"

#include "spieler.h"
#include "data.h"

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

void DreiSpielerDialog::on_buttonBox_accepted()
{

    data::spieler[0].mName = ui ->spielerName31->text().trimmed();
    data::spieler[1].mName = ui ->spielerName32->text().trimmed();
    data::spieler[2].mName = ui ->spielerName33->text().trimmed();

    this->close();

}

