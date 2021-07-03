#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);
}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
}

void singleplayerDialog::on_buttonBox_rejected()        //Der SingleplayerModus wird geschlossen ohne die Daten zu speichern
{
    this->close();
}

