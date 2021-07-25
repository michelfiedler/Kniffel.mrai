#include "dreispielerdialog.h"
#include "ui_dreispielerdialog.h"

#include "spieler.h"

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
    Spieler spieler;

    spieler.mName1 = ui ->spielerName31->text().trimmed();              //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName32->text().trimmed();
    spieler.mName3 = ui ->spielerName33->text().trimmed();

    this->close();

}

