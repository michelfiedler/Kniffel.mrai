#include "multiplayerdialog.h"
#include "ui_multiplayerdialog.h"

#include "spieler.h"
#include "zweispielerdialog.h"
#include "dreispielerdialog.h"
#include "vierspielerdialog.h"
#include "fuenfspielerdialog.h"
#include "sechsspielerdialog.h"
#include "siebenspielerdialog.h"

#include "QTableWidget"
#include "data.h"
#include <QString>
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

    data::spieleranzahl = (Spieler::eSpieleranzahl) ui-> cBSpieleranzahl->currentIndex(); /* Die Anzahl der Spieler wird in der Combobox angegen
                                                                                          und in der Variable mSpieleranzahl gespeichert.*/

    data::spieler = new Spieler[data::spieleranzahl];

    switch (data::spieleranzahl)             //Abhängigt von der Spieleranzahl öffnet sich ein neues Fenster, in der passend zur Anzahl der Spieler die Namen eingetragen werden können
    {
        case 0:                     //Das Fenster zur Eingabe von zwei Spielernamen öffnet sich.
        {
            ZweiSpielerDialog* zweiSpielerDialog = new ZweiSpielerDialog(this);
            zweiSpielerDialog->show();

            break;

        }

        case 1:                     //Das Fenster zur Eingabe von drei Spielernamen öffnet sich.
        {
             DreiSpielerDialog* dreiSpielerDialog = new DreiSpielerDialog(this);
             dreiSpielerDialog->show();
             break;
        }

        case 2:                     //Das Fenster zur Eingabe von vier Spielernamen öffnet sich.
        {
            VierSpielerDialog* vierSpielerDialog = new VierSpielerDialog(this);
            vierSpielerDialog->show();
            break;
        }
         case 3:                    //Das Fenster zur Eingabe von fuenf Spielernamen öffnet sich.
        {
            FuenfSpielerDialog* fuenfSpielerDialog = new FuenfSpielerDialog(this);
            fuenfSpielerDialog->show();
            break;
        }
         case 4:                    //Das Fenster zur Eingabe von sechs Spielernamen öffnet sich.
        {
            SechsSpielerDialog* sechsSpielerDialog = new SechsSpielerDialog(this);
            sechsSpielerDialog->show();
            break;
        }
        case 5:                     //Das Fenster zur Eingabe von sieben Spielernamen öffnet sich.
        {
            SiebenSpielerDialog* siebenSpielerDialog = new SiebenSpielerDialog(this);
            siebenSpielerDialog->show();
            break;
        }
    }



}

void MultiplayerDialog::fillNameTable()                     //Funktion füllt die Tabelle im Multiplayerdialog mit den eingegebenen Namen
{
    int mSpieleranzahl = (Spieler::eSpieleranzahl) ui-> cBSpieleranzahl->currentIndex();    /* Die Anzahl der Spieler wird in der Combobox angegen
                                                                                          und in der Variable mSpieleranzahl gespeichert.*/

    ui->tBSpielernamen->setRowCount(0);          //Bisherige Einträge werden gelöscht

    for (int i=0; i<mSpieleranzahl; i++)            //Abhängig von der Spieleranzahl werden die eingespeicherten Namen pro Reihe in der Tabelle eingetragen
    {
        ui->tBSpielernamen->insertRow(ui->tBSpielernamen->rowCount());
        ui->tBSpielernamen->setItem(ui->tBSpielernamen->rowCount() -1,i, new QTableWidgetItem(QString(data::spieler[i].mName)));
    }

}

