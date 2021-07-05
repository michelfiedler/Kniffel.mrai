#include "multiplayerdialog.h"
#include "ui_multiplayerdialog.h"

MultiplayerDialog::MultiplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiplayerDialog)
{
    ui->setupUi(this);
}

MultiplayerDialog::~MultiplayerDialog()
{
    delete ui;
}
