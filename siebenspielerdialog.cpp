#include "siebenspielerdialog.h"
#include "ui_siebenspielerdialog.h"

#include "spieler.h"

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
    Spieler spieler;

    spieler.mName1 = ui ->spielerName71->text().trimmed();              //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName72->text().trimmed();
    spieler.mName3 = ui ->spielerName73->text().trimmed();
    spieler.mName4 = ui ->spielerName74->text().trimmed();
    spieler.mName5 = ui ->spielerName75->text().trimmed();
    spieler.mName6 = ui ->spielerName76->text().trimmed();
    spieler.mName7 = ui ->spielerName77->text().trimmed();

    this->close();
}

