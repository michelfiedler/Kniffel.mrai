#include "vierspielerdialog.h"
#include "ui_vierspielerdialog.h"

#include "spieler.h"
#include "data.h"

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

void VierSpielerDialog::on_buttonBox_accepted()
{

    data::spieler[0].mName = ui ->spielerName41->text().trimmed();
    data::spieler[1].mName = ui ->spielerName42->text().trimmed();
    data::spieler[2].mName = ui ->spielerName43->text().trimmed();
    data::spieler[3].mName = ui ->spielerName44->text().trimmed();//Die eingegebenen Namen werden gespeichert.


    this->close();
}

