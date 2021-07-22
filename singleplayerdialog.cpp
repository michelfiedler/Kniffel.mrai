#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"
#include "data.h"
#include "Funktionen.h"

#include <QObject>
#include <QMessageBox>
#include <QLCDNumber>
#include <QLabel>

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);

    data::singleSpieler.Spielstand = new int [13]; //Ein Spielstand Feld für den SinglePlayer erstellen
    for (int i=0; i<13; i++) {data::singleSpieler.Spielstand[i]=0;} //Alle Einträge des Spielstandes auf 0 setzen

    QObject::connect(this, &singleplayerDialog::besetzt, this, &singleplayerDialog::neuWaehlen);    //Der Slot neuWaehlen und das Signal besetzt werden verknüpft

}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
    //Dynamisch angeforderten Speicher wieder freigeben
    delete [] data::singleSpieler.Spielstand;
    data::singleSpieler.Spielstand = NULL;
}


//Slots

void singleplayerDialog::on_buttonBox_rejected()        //Der SingleplayerModus wird geschlossen
{
    this->close();
}

void singleplayerDialog::on_tW_SpielstandSingle_cellClicked(int row, int column)    //Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden
{
    ui->tW_SpielstandSingle->setSortingEnabled(false);  //Sortieren der Tabelle abschalten

    if (column!=1)       //Dafür sorgen, dass nur ins Spieler-Feld und nicht ins KI-Feld eingetragen wird
    {
        //Jedes Event beschreibt das Spielstandfeld und setzt den erwünschten Wert aus dem Spielstand in die Tabelle ein
        if (row==0) //Einsen
        {
            if (!(ui->tW_SpielstandSingle->item(0,0))) { write (dice, data::singleSpieler.Spielstand, 1); //Testen, ob schon ein Item existiert und wenn nicht, den Spielstand beschreiben
                QTableWidgetItem *item= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[0])); //ein Item für die Tabelle erstellen und den Eintrag in einen integer umwandeln, um die Punkte des Spielstandes einzutragen
                ui->tW_SpielstandSingle->setItem(0,0, item);} //Das Item in die Tabelle einfügen
            else {emit besetzt();}            //Signal für erneute Feldauswahl, falls in diesem Feld schon Punkte eingetragen wurden

        }
        else if (row==1) //Zweien
        {
            if (!(ui->tW_SpielstandSingle->item(1,0))) {write (dice, data::singleSpieler.Spielstand, 2);
                QTableWidgetItem *item1= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[1]));
                ui->tW_SpielstandSingle->setItem (1,0,item1);}
            else {emit besetzt();}

        }
        else if (row==2) //Dreien
        {
            if (!(ui->tW_SpielstandSingle->item(2,0))) {write (dice, data::singleSpieler.Spielstand, 3);
                QTableWidgetItem *item2= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[2]));
                ui->tW_SpielstandSingle->setItem (2,0,item2);}
            else {emit besetzt();}

        }
        else if (row==3) //Vieren
        {
            if (!(ui->tW_SpielstandSingle->item(3,0))) {write (dice, data::singleSpieler.Spielstand, 4);
                QTableWidgetItem *item3= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[3]));
                ui->tW_SpielstandSingle->setItem (3,0,item3);}
            else {emit besetzt();}

        }
        else if (row==4)//Fünfen
        {
            if (!(ui->tW_SpielstandSingle->item(4,0))) {write (dice, data::singleSpieler.Spielstand, 5);
                QTableWidgetItem *item4= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[4]));
                ui->tW_SpielstandSingle->setItem (4,0,item4);}
            else {emit besetzt();}

        }
        else if (row==5) //Sechsen
        {
            if (!(ui->tW_SpielstandSingle->item(5,0))) {write (dice, data::singleSpieler.Spielstand, 6);
                QTableWidgetItem *item5= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[5]));
                ui->tW_SpielstandSingle->setItem (5,0,item5);}
            else {emit besetzt();}

        }
        else if (row==6) //Dreierpasch
        {
            if (!(ui->tW_SpielstandSingle->item(6,0))) {write (dice, data::singleSpieler.Spielstand, 7);
                QTableWidgetItem *item6= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[6]));
                ui->tW_SpielstandSingle->setItem(6,0,item6);}
            else {emit besetzt();}

        }
        else if (row==7) //Viererpasch
        {
            if (!(ui->tW_SpielstandSingle->item(7,0))) {write (dice, data::singleSpieler.Spielstand, 8);
                QTableWidgetItem *item7= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[7]));
                ui->tW_SpielstandSingle->setItem(7,0,item7);}
            else {emit besetzt();}
        }
        else if (row==8) //FullHouse
        {
           if (!(ui->tW_SpielstandSingle->item(8,0))) {write (dice, data::singleSpieler.Spielstand, 9);
               QTableWidgetItem *item8= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[8]));
                ui->tW_SpielstandSingle->setItem(8,0,item8);}
           else {emit besetzt();}
        }
        else if (row==9) //kl Strasse
        {
            if (!(ui->tW_SpielstandSingle->item(9,0))) {write (dice, data::singleSpieler.Spielstand, 10);
                QTableWidgetItem *item9= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[9]));
                ui->tW_SpielstandSingle->setItem(9,0,item9);}
            else {emit besetzt();}
        }
        else if (row==10) //gr Strasse
        {
            if (!(ui->tW_SpielstandSingle->item(10,0))) {write (dice, data::singleSpieler.Spielstand, 11);
                QTableWidgetItem *item10= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[10]));
                ui->tW_SpielstandSingle->setItem(10,0,item10);}
            else {emit besetzt();}
        }
        else if (row==11) //Kniffel
        {
            if (!(ui->tW_SpielstandSingle->item(11,0))) {write (dice, data::singleSpieler.Spielstand, 12);
                QTableWidgetItem *item11= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[11]));
                ui->tW_SpielstandSingle->setItem(11,0,item11);}
            else {emit besetzt();}
        }
        else if (row==12) //Chance
        {
            if (!(ui->tW_SpielstandSingle->item(12,0))) {write (dice, data::singleSpieler.Spielstand, 13);
                QTableWidgetItem *item12= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[12]));
                ui->tW_SpielstandSingle->setItem(12,0,item12);}
            else {emit besetzt();}
        }
    }
    else {emit besetzt();}        //Signal für erneute Feldauswahl
}

void singleplayerDialog::neuWaehlen()   //Slot, der MessageBox anzeigt, welche den Benutzer auffordert ein neues Feld zu wählen
{
    QMessageBox msgBox;
    msgBox.setText("Dieses Feld kann nicht beschrieben werden. Bitte wählen Sie ein anderes aus.");
    msgBox.exec();
}


void singleplayerDialog::on_pBwuerfeln_clicked()    //Würfelt und zeigt die Würfelergebnisse an
{
    ui->pBW1->setChecked(false);    //Die Buttons für das Behalten werden zurückgesetzt->sie "leuchten" nicht mehr
    ui->pBW2->setChecked(false);
    ui->pBW3->setChecked(false);
    ui->pBW4->setChecked(false);
    ui->pBW5->setChecked(false);
    if(data::wievielterWurf==0) for(int i=0; i<5; i++) keep[i] = 0;
    if(data::wievielterWurf<3){     //Man kann nicht mehr als 3 mal würfeln
    rolldice(dice,keep);
    for(int i=0; i<5; i++) keep[i]=0;   //nach jedem Wurf wird das keep Feld wieder mit 0 beschrieben

    //Variablen für die Bilder der Würfel anlegen
    QPixmap augen1 (":/MyImages/imageWuerfel1.png");
    QPixmap augen2 (":/MyImages/imageWuerfel2.png");
    QPixmap augen3 (":/MyImages/imageWuerfel3.png");
    QPixmap augen4 (":/MyImages/imageWuerfel4.png");
    QPixmap augen5 (":/MyImages/imageWuerfel5.png");
    QPixmap augen6 (":/MyImages/imageWuerfel6.png");

    //Für den gewürfelten Wert von Würfel 1 das entsprechende Bild einfügen
    if(dice[0]==1) {ui->qlW1->setPixmap(augen1);}
    if(dice[0]==2) {ui->qlW1->setPixmap(augen2);}
    if(dice[0]==3) {ui->qlW1->setPixmap(augen3);}
    if(dice[0]==4) {ui->qlW1->setPixmap(augen4);}
    if(dice[0]==5) {ui->qlW1->setPixmap(augen5);}
    if(dice[0]==6) {ui->qlW1->setPixmap(augen6);}

    //Für den gewürfelten Wert von Würfel 2 das entsprechende Bild einfügen
    if(dice[1]==1) {ui->qlW2->setPixmap(augen1);}
    if(dice[1]==2) {ui->qlW2->setPixmap(augen2);}
    if(dice[1]==3) {ui->qlW2->setPixmap(augen3);}
    if(dice[1]==4) {ui->qlW2->setPixmap(augen4);}
    if(dice[1]==5) {ui->qlW2->setPixmap(augen5);}
    if(dice[1]==6) {ui->qlW2->setPixmap(augen6);}

    //Für den gewürfelten Wert von Würfel 3 das entsprechende Bild einfügen
    if(dice[2]==1) {ui->qlW3->setPixmap(augen1);}
    if(dice[2]==2) {ui->qlW3->setPixmap(augen2);}
    if(dice[2]==3) {ui->qlW3->setPixmap(augen3);}
    if(dice[2]==4) {ui->qlW3->setPixmap(augen4);}
    if(dice[2]==5) {ui->qlW3->setPixmap(augen5);}
    if(dice[2]==6) {ui->qlW3->setPixmap(augen6);}

    //Für den gewürfelten Wert von Würfel 4 das entsprechende Bild einfügen
    if(dice[3]==1) {ui->qlW4->setPixmap(augen1);}
    if(dice[3]==2) {ui->qlW4->setPixmap(augen2);}
    if(dice[3]==3) {ui->qlW4->setPixmap(augen3);}
    if(dice[3]==4) {ui->qlW4->setPixmap(augen4);}
    if(dice[3]==5) {ui->qlW4->setPixmap(augen5);}
    if(dice[3]==6) {ui->qlW4->setPixmap(augen6);}

    //Für den gewürfelten Wert von Würfel 5 das entsprechende Bild einfügen
    if(dice[4]==1) {ui->qlW5->setPixmap(augen1);}
    if(dice[4]==2) {ui->qlW5->setPixmap(augen2);}
    if(dice[4]==3) {ui->qlW5->setPixmap(augen3);}
    if(dice[4]==4) {ui->qlW5->setPixmap(augen4);}
    if(dice[4]==5) {ui->qlW5->setPixmap(augen5);}
    if(dice[4]==6) {ui->qlW5->setPixmap(augen6);}

    data::wievielterWurf++;
    }
}

//Slots für das Behalten oder nicht Behalten der Würfel
void singleplayerDialog::on_pBW1_clicked()
{
    if(ui->pBW1->isChecked())keep[0]=1; //Wenn die Buttons gedrückt werden, soll der Würfel behalten werden->der behalten Button "leuchtet" in dem Fall
    else keep[0]=0;
}


void singleplayerDialog::on_pBW2_clicked()
{
    if(ui->pBW2->isChecked())keep[1]=1;
    else keep[1]=0;
}


void singleplayerDialog::on_pBW3_clicked()
{
    if(ui->pBW3->isChecked())keep[2]=1;
    else keep[2]=0;
}


void singleplayerDialog::on_pBW4_clicked()
{
    if(ui->pBW4->isChecked())keep[3]=1;
    else keep[3]=0;
}


void singleplayerDialog::on_pBW5_clicked()
{
    if(ui->pBW5->isChecked())keep[4]=1;
    else keep[4]=0;
}

