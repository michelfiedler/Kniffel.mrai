#include "vierspielerdialog.h"
#include "ui_vierspielerdialog.h"

#include "spieler.h"

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
    Spieler spieler;

    spieler.mName1 = ui ->spielerName41->text().trimmed();              //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName42->text().trimmed();
    spieler.mName3 = ui ->spielerName43->text().trimmed();
    spieler.mName4 = ui ->spielerName44->text().trimmed();

    this->close();
}

