#include "sechsspielerdialog.h"
#include "ui_sechsspielerdialog.h"

#include "spieler.h"
#include "data.h"

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

    data::spieler[0].mName = ui ->spielerName61->text().trimmed();
    data::spieler[1].mName = ui ->spielerName62->text().trimmed();
    data::spieler[2].mName = ui ->spielerName63->text().trimmed();
    data::spieler[3].mName = ui ->spielerName64->text().trimmed();
    data::spieler[4].mName = ui ->spielerName65->text().trimmed();
    data::spieler[5].mName = ui ->spielerName66->text().trimmed();



    this->close();
}

