#include "siebenspielerdialog.h"
#include "ui_siebenspielerdialog.h"

#include "spieler.h"
#include "data.h"

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

void SiebenSpielerDialog::on_buttonBox_accepted()
{


    data::spieler[0].mName = ui ->spielerName71->text().trimmed();      //Die eingegebenen Namen werden gespeichert.
    data::spieler[1].mName = ui ->spielerName72->text().trimmed();
    data::spieler[2].mName = ui ->spielerName73->text().trimmed();
    data::spieler[3].mName = ui ->spielerName74->text().trimmed();
    data::spieler[4].mName = ui ->spielerName75->text().trimmed();
    data::spieler[5].mName = ui ->spielerName76->text().trimmed();
    data::spieler[6].mName = ui ->spielerName77->text().trimmed();

    emit tabelleFuellen7();

    this->close();
}

