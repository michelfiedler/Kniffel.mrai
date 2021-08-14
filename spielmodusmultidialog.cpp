#include "spielmodusmultidialog.h"
#include "ui_spielmodusmultidialog.h"
#include "data.h"
#include "Funktionen.h"

#include <QObject>
#include <QLabel>
#include <QMessageBox>

spielmodusMultiDialog::spielmodusMultiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spielmodusMultiDialog)
{
    ui->setupUi(this);

    ui->tW_SpielstandMulti->setColumnCount(data::spieleranzahl+2);  //Anzahl der Spalten im Kniffelblatt an Spieleranzahl anpassen
    for(int i=0; i<=data::spieleranzahl+1; i++)     //i läuft von 0 bis Anzahl der Spieler -1 für den Index der Spalten
    {
        data::spieler[i].Spielstand = new int [13]; //Ein Spielstand Feld für die Spieler
        data::spieler[i].reset_Spielstand();

        ui->tW_SpielstandMulti->setHorizontalHeaderItem(i,new QTableWidgetItem(QString(data::spieler[i].mName)));   //Namen der Spieler im Kniffelblatt eintragen

        QObject::connect(this, &spielmodusMultiDialog::wrongCell, this, &spielmodusMultiDialog::chooseNewCell);
    }

}

spielmodusMultiDialog::~spielmodusMultiDialog()
{
    delete ui;

    //Dynamisch angeforderten Speicher wieder freigeben
    for(int i=0; i<=data::spieleranzahl+1; i++)
    {
        delete [] data::spieler[i].Spielstand;
        data::spieler[i].Spielstand = NULL;
    }
}

void spielmodusMultiDialog::on_buttonBox_rejected()
{
    this->close();
}


void spielmodusMultiDialog::on_tW_SpielstandMulti_cellClicked(int row, int column)
{
    ui->tW_SpielstandMulti->setSortingEnabled(false);

    if(column==data::welcherSpieler)        //welcherSpieler muss nach jedem mal würfeln neu definiert werden, damit definiert wird welcher Spieler am Zug ist
    {
        if(data::spieler[data::welcherSpieler].Spielstand[row] == 888)
        {
            write (dice, data::spieler[data::welcherSpieler].Spielstand, row+1); //Testen, ob schon ein Item existiert und wenn nicht, den Spielstand beschreiben
            QTableWidgetItem *item= new QTableWidgetItem(QString::number(data::spieler[data::welcherSpieler].Spielstand[row])); //ein Item für die Tabelle erstellen und den Eintrag in einen integer umwandeln, um die Punkte des Spielstandes einzutragen
            ui->tW_SpielstandMulti->setItem(row,data::welcherSpieler, item);
            if(data::welcherSpieler==data::spieleranzahl+1) //War der letzte Spieler der Gruppe dran, wird definiert, dass wieder der Erste dran ist.
            {
                data::welcherSpieler=0;
                data::Zug++;
            }
            else {data::welcherSpieler+=1;} //Definieren, dass der nächste Spieler dran ist.
        }
        else {emit wrongCell();}
    }
    else {emit wrongCell();}
}

void spielmodusMultiDialog::chooseNewCell()
{
    QMessageBox myMsgBox;
    myMsgBox.setText("Dieses Feld kannst Du nicht beschreiben. Bitte wähle ein anderes aus.");
    myMsgBox.exec();
}


void spielmodusMultiDialog::on_pBwuerfeln_clicked()
{
    ui->pBW1->setChecked(false);    //Die Buttons für das Behalten werden zurückgesetzt->sie "leuchten" nicht mehr
    ui->pBW2->setChecked(false);
    ui->pBW3->setChecked(false);
    ui->pBW4->setChecked(false);
    ui->pBW5->setChecked(false);
    if(data::wievielterWurf<3)     //Man kann nicht mehr als 3 mal würfeln
    {
        rolldice(dice,keep);
        for(int i=0; i<5; i++) keep[i]=0;   //nach jedem Wurf wird das keep Feld wieder mit 0 beschrieben

        //Variablen für die Bilder der Würfel anlegen
        QPixmap multiAugen1 (":/MyImages/imageWuerfel1.png");
        QPixmap multiAugen2 (":/MyImages/imageWuerfel2.png");
        QPixmap multiAugen3 (":/MyImages/imageWuerfel3.png");
        QPixmap multiAugen4 (":/MyImages/imageWuerfel4.png");
        QPixmap multiAugen5 (":/MyImages/imageWuerfel5.png");
        QPixmap multiAugen6 (":/MyImages/imageWuerfel6.png");

        //Für den gewürfelten Wert von Würfel 1 das entsprechende Bild einfügen
        if(dice[0]==1) {ui->qlW1->setPixmap(multiAugen1);}
        if(dice[0]==2) {ui->qlW1->setPixmap(multiAugen2);}
        if(dice[0]==3) {ui->qlW1->setPixmap(multiAugen3);}
        if(dice[0]==4) {ui->qlW1->setPixmap(multiAugen4);}
        if(dice[0]==5) {ui->qlW1->setPixmap(multiAugen5);}
        if(dice[0]==6) {ui->qlW1->setPixmap(multiAugen6);}

        //Für den gewürfelten Wert von Würfel 2 das entsprechende Bild einfügen
        if(dice[1]==1) {ui->qlW2->setPixmap(multiAugen1);}
        if(dice[1]==2) {ui->qlW2->setPixmap(multiAugen2);}
        if(dice[1]==3) {ui->qlW2->setPixmap(multiAugen3);}
        if(dice[1]==4) {ui->qlW2->setPixmap(multiAugen4);}
        if(dice[1]==5) {ui->qlW2->setPixmap(multiAugen5);}
        if(dice[1]==6) {ui->qlW2->setPixmap(multiAugen6);}

        //Für den gewürfelten Wert von Würfel 3 das entsprechende Bild einfügen
        if(dice[2]==1) {ui->qlW3->setPixmap(multiAugen1);}
        if(dice[2]==2) {ui->qlW3->setPixmap(multiAugen2);}
        if(dice[2]==3) {ui->qlW3->setPixmap(multiAugen3);}
        if(dice[2]==4) {ui->qlW3->setPixmap(multiAugen4);}
        if(dice[2]==5) {ui->qlW3->setPixmap(multiAugen5);}
        if(dice[2]==6) {ui->qlW3->setPixmap(multiAugen6);}

        //Für den gewürfelten Wert von Würfel 4 das entsprechende Bild einfügen
        if(dice[3]==1) {ui->qlW4->setPixmap(multiAugen1);}
        if(dice[3]==2) {ui->qlW4->setPixmap(multiAugen2);}
        if(dice[3]==3) {ui->qlW4->setPixmap(multiAugen3);}
        if(dice[3]==4) {ui->qlW4->setPixmap(multiAugen4);}
        if(dice[3]==5) {ui->qlW4->setPixmap(multiAugen5);}
        if(dice[3]==6) {ui->qlW4->setPixmap(multiAugen6);}

        //Für den gewürfelten Wert von Würfel 5 das entsprechende Bild einfügen
        if(dice[4]==1) {ui->qlW5->setPixmap(multiAugen1);}
        if(dice[4]==2) {ui->qlW5->setPixmap(multiAugen2);}
        if(dice[4]==3) {ui->qlW5->setPixmap(multiAugen3);}
        if(dice[4]==4) {ui->qlW5->setPixmap(multiAugen4);}
        if(dice[4]==5) {ui->qlW5->setPixmap(multiAugen5);}
        if(dice[4]==6) {ui->qlW5->setPixmap(multiAugen6);}

        data::wievielterWurf++;
    }
}

