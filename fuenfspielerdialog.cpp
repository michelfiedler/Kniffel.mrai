#include "fuenfspielerdialog.h"
#include "ui_fuenfspielerdialog.h"

#include "spieler.h"
#include "data.h"

FuenfSpielerDialog::FuenfSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuenfSpielerDialog)
{
    ui->setupUi(this);
}

FuenfSpielerDialog::~FuenfSpielerDialog()
{
    delete ui;
}

void FuenfSpielerDialog::on_buttonBox_accepted()
{

    data::spieler[0].mName = ui ->spielerName51->text().trimmed();
    data::spieler[1].mName = ui ->spielerName52->text().trimmed();
    data::spieler[2].mName = ui ->spielerName53->text().trimmed();
    data::spieler[3].mName = ui ->spielerName54->text().trimmed();
    data::spieler[4].mName = ui ->spielerName55->text().trimmed();
                 //Die eingegebenen Namen werden gespeichert.


    this->close();
}

