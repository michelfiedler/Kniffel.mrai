#include "sechsspielerdialog.h"
#include "ui_sechsspielerdialog.h"

#include "spieler.h"

SechsSpielerDialog::SechsSpielerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SechsSpielerDialog)
{
    ui->setupUi(this);
}

SechsSpielerDialog::~SechsSpielerDialog()
{
    delete ui;
}

void SechsSpielerDialog::on_buttonBox_accepted()
{
    Spieler spieler;

    spieler.mName1 = ui ->spielerName61->text().trimmed();              //Die eingegebenen Namen werden gespeichert.
    spieler.mName2 = ui ->spielerName62->text().trimmed();
    spieler.mName3 = ui ->spielerName63->text().trimmed();
    spieler.mName4 = ui ->spielerName64->text().trimmed();
    spieler.mName5 = ui ->spielerName65->text().trimmed();
    spieler.mName6 = ui ->spielerName66->text().trimmed();

    this->close();
}

