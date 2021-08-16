#include "zweispielerdialog.h"
#include "ui_zweispielerdialog.h"

#include "spieler.h"
#include "data.h"

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

    data::spieler[0].mName = ui ->nameEins->text().trimmed();               //Die eingegebenen Namen werden gespeichert.
    data::spieler[1].mName = ui ->spielerName22->text().trimmed();

    emit tabelleFuellen2();

    this->close();
}

