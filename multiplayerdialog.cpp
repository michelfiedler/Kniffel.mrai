#include "multiplayerdialog.h"
#include "ui_multiplayerdialog.h"

#include "spieler.h"
#include "zweispielerdialog.h"
#include "dreispielerdialog.h"

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




void MultiplayerDialog::on_pBNamenEintragen_clicked()
{

    int mSpieleranzahl = (Spieler::eSpieleranzahl) ui-> cBSpieleranzahl->currentIndex();



    switch (mSpieleranzahl)
    {
        case 0:
        {
            ZweiSpielerDialog* zweiSpielerDialog = new ZweiSpielerDialog(this);
            zweiSpielerDialog->show();
             break;

        }

        case 1:
        {
             DreiSpielerDialog* dreiSpielerDialog = new DreiSpielerDialog(this);
             dreiSpielerDialog->show();
             break;
        }

        case 2:
        {

        }
         case 3:
        {

        }
         case 4:
        {

        }
        case 5:
        {

        }
    }



}

