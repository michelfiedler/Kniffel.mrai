#include "fuenfspielerdialog.h"
#include "ui_fuenfspielerdialog.h"

#include "spieler.h"

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
    Spieler spieler;

    spieler.mName1 = ui ->spielerName51->text().trimmed();              //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName52->text().trimmed();
    spieler.mName3 = ui ->spielerName53->text().trimmed();
    spieler.mName4 = ui ->spielerName54->text().trimmed();
    spieler.mName5 = ui ->spielerName55->text().trimmed();

    this->close();
}

