#include "zweispielerdialog.h"
#include "ui_zweispielerdialog.h"

#include "spieler.h"

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

void ZweiSpielerDialog::on_buttonBox_accepted()
{
    Spieler spieler;

    spieler.mName1 = ui ->nameEins->text().trimmed();               //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName22->text().trimmed();

    this->close();
}

