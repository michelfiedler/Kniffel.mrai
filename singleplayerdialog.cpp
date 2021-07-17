#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"
#include "data.h"
#include "Funktionen.h"

#include <QObject>
#include <QMessageBox>
#include <QLCDNumber>

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);

    QObject::connect(this, &singleplayerDialog::besetzt, this, &singleplayerDialog::neuWaehlen);    //Der Slot neuWaehlen und das Signal besetzt werden verküpft
    //Die Signale und Slots, die angeben welches Feld im Gewinnblatt ausgewählt wurde und dieses beschreiben, verknüpfen
    QObject::connect(this, &singleplayerDialog::wahlEinsen, this, &singleplayerDialog::einsenGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlZweien, this, &singleplayerDialog::zweienGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlDreien, this, &singleplayerDialog::dreienGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlVieren, this, &singleplayerDialog::vierenGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlFuenfen, this, &singleplayerDialog::fuenfenGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlSechsen, this, &singleplayerDialog::sechsenGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlDreierpasch, this, &singleplayerDialog::dreierpaschGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlViererpasch, this, &singleplayerDialog::viererpaschGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlFullHouse, this, &singleplayerDialog::fullhouseGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlKlStrasse, this, &singleplayerDialog::klstrasseGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlGrStrasse, this, &singleplayerDialog::grstrasseGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlKniffel, this, &singleplayerDialog::kniffelGewaehlt);
    QObject::connect(this, &singleplayerDialog::wahlChance, this, &singleplayerDialog::chanceGewaehlt);
}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
}


//Slots

void singleplayerDialog::on_buttonBox_rejected()        //Der SingleplayerModus wird geschlossen
{
    this->close();
}

void singleplayerDialog::on_tW_SpielstandSingle_cellClicked(int row, int column)    //Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden
{
    if (column!=1)       //Dafür sorgen, dass nur ins Spieler-Feld und nicht ins KI-Feld eingetragen wird
    {
        //Jedes event sendet Signal, dass das ausgewählte entsprechende Feld im Spielstand beschrieben werden soll und setzt dann die Punkte aus dem Spielstand in die Tabelle ein
        if (row==0) //Einsen
        {
            if (ui->tW_SpielstandSingle->item(0,0)==NULL) {emit wahlEinsen();
                ui->tW_SpielstandSingle->setItem (0,0, new QTableWidgetItem (data::singleSpieler.Spielstand[0]));}
            else {emit besetzt();}            //Signal für erneute Feldauswahl, falls in diesem Feld schon Punkte eingetragen wurden

        }
        else if (row==1) //Zweien
        {
            if (ui->tW_SpielstandSingle->item(1,0)==NULL) {emit wahlZweien();
                ui->tW_SpielstandSingle->setItem (1,0,new QTableWidgetItem (data::singleSpieler.Spielstand[1]));}
            else {emit besetzt();}

        }
        else if (row==2) //Dreien
        {
            if (ui->tW_SpielstandSingle->item(2,0)==NULL) {emit wahlDreien();
                ui->tW_SpielstandSingle->setItem (2,0,new QTableWidgetItem (data::singleSpieler.Spielstand[2]));}
            else {emit besetzt();}

        }
        else if (row==3) //Vieren
        {
            if (ui->tW_SpielstandSingle->item(3,0)==NULL) {emit wahlVieren();
                ui->tW_SpielstandSingle->setItem (3,0,new QTableWidgetItem (data::singleSpieler.Spielstand[3]));}
            else {emit besetzt();}

        }
        else if (row==4)//Fünfen
        {
            if (ui->tW_SpielstandSingle->item(4,0)==NULL) {emit wahlFuenfen();
                ui->tW_SpielstandSingle->setItem (4,0,new QTableWidgetItem (data::singleSpieler.Spielstand[4]));}
            else {emit besetzt();}

        }
        else if (row==5) //Sechsen
        {
            if (ui->tW_SpielstandSingle->item(5,0)==NULL) {emit wahlSechsen();
                ui->tW_SpielstandSingle->setItem (5,0,new QTableWidgetItem (data::singleSpieler.Spielstand[5]));}
            else {emit besetzt();}

        }
        else if (row==6) //Dreierpasch
        {
            if (ui->tW_SpielstandSingle->item(6,0)==NULL) {emit wahlDreierpasch();
                ui->tW_SpielstandSingle->setItem(6,0,new QTableWidgetItem (data::singleSpieler.Spielstand[6]));}
            else {emit besetzt();}

        }
        else if (row==7) //Viererpasch
        {
            if (ui->tW_SpielstandSingle->item(7,0)==NULL) {emit wahlViererpasch();
                ui->tW_SpielstandSingle->setItem(7,0,new QTableWidgetItem (data::singleSpieler.Spielstand[7]));}
            else {emit besetzt();}
        }
        else if (row==8) //FullHouse
        {
           if (ui->tW_SpielstandSingle->item(8,0)==NULL) {emit wahlFullHouse();
                ui->tW_SpielstandSingle->setItem(8,0,new QTableWidgetItem (data::singleSpieler.Spielstand[8]));}
           else {emit besetzt();}
        }
        else if (row==9) //kl Strasse
        {
            if (ui->tW_SpielstandSingle->item(9,0)==NULL) {emit wahlKlStrasse();
                ui->tW_SpielstandSingle->setItem(9,0,new QTableWidgetItem (data::singleSpieler.Spielstand[9]));}
            else {emit besetzt();}
        }
        else if (row==10) //gr Strasse
        {
            if (ui->tW_SpielstandSingle->item(10,0)==NULL) {emit wahlGrStrasse();
                ui->tW_SpielstandSingle->setItem(10,0,new QTableWidgetItem (data::singleSpieler.Spielstand[10]));}
            else {emit besetzt();}
        }
        else if (row==11) //Kniffel
        {
            if (ui->tW_SpielstandSingle->item(11,0)==NULL) {emit wahlKniffel();
                ui->tW_SpielstandSingle->setItem(11,0,new QTableWidgetItem (data::singleSpieler.Spielstand[11]));}
            else {emit besetzt();}
        }
        else if (row==12) //Chance
        {
            if (ui->tW_SpielstandSingle->item(12,0)==NULL) {emit wahlChance();
                ui->tW_SpielstandSingle->setItem(12,0,new QTableWidgetItem (data::singleSpieler.Spielstand[12]));}
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

void singleplayerDialog::einsenGewaehlt()   //Slot, der im Spielstand die Einsen einträgt
{
    write (dice, data::singleSpieler.Spielstand, 1);
}

void singleplayerDialog::zweienGewaehlt()   //Slot, der im Spielstand die Zweien einträgt
{
    write (dice, data::singleSpieler.Spielstand, 2);
}

void singleplayerDialog::dreienGewaehlt()   //Slot, der im Spielstand der Dreien einträgt
{
    write (dice, data::singleSpieler.Spielstand, 3);
}

void singleplayerDialog::vierenGewaehlt()   //Slot, der im Spielstand der Vieren einträgt
{
    write (dice, data::singleSpieler.Spielstand, 4);
}

void singleplayerDialog::fuenfenGewaehlt()   //Slot, der im Spielstand der Fünfen einträgt
{
    write (dice, data::singleSpieler.Spielstand, 5);
}

void singleplayerDialog::sechsenGewaehlt()   //Slot, der im Spielstand der Sechsen einträgt
{
    write (dice, data::singleSpieler.Spielstand, 6);
}

void singleplayerDialog::dreierpaschGewaehlt()   //Slot, der im Spielstand die Punkte für einen Dreierpasch einträgt
{
    write (dice, data::singleSpieler.Spielstand, 7);
}

void singleplayerDialog::viererpaschGewaehlt()   //Slot, der im Spielstand die Punkte für einen Viererpasch einträgt
{
    write (dice, data::singleSpieler.Spielstand, 8);
}

void singleplayerDialog::fullhouseGewaehlt()   //Slot, der im Spielstand die Punkte für ein Full House einträgt
{
    write (dice, data::singleSpieler.Spielstand, 9);
}

void singleplayerDialog::klstrasseGewaehlt()   //Slot, der im Spielstand die Punkte für eine kleine Straße einträgt
{
    write (dice, data::singleSpieler.Spielstand, 10);
}

void singleplayerDialog::grstrasseGewaehlt()   //Slot, der im Spielstand die Punkte für eine große Straße einträgt
{
    write (dice, data::singleSpieler.Spielstand, 11);
}

void singleplayerDialog::kniffelGewaehlt()   //Slot, der im Spielstand die Punkte für einen Kniffel einträgt
{
    write (dice, data::singleSpieler.Spielstand, 12);
}

void singleplayerDialog::chanceGewaehlt()   //Slot, der im Spielstand die Punkte für eine Chance einträgt
{
    write (dice, data::singleSpieler.Spielstand, 13);
}

void singleplayerDialog::on_pBwuerfeln_clicked()    //Würfelt und zeigt die Würfelergebnisse an
{
    if(data::wievielterWurf==0) for(int i=0; i<5; i++) keep[i] = 0;
    if(data::wievielterWurf<3){     //Man kann nicht mehr als 3 mal würfeln
    rolldice(dice,keep);
    for(int i=0; i<5; i++) keep[i]=0;   //nach jedem Wurf wird das keep Feld wieder mit 0 beschrieben
    ui->lcdNumber_1->display(dice[0]);
    ui->lcdNumber_2->display(dice[1]);
    ui->lcdNumber_3->display(dice[2]);
    ui->lcdNumber_4->display(dice[3]);
    ui->lcdNumber_5->display(dice[4]);
    data::wievielterWurf++;
    }
}

//Slots für das Behalten oder nicht Behalten der Würfel
void singleplayerDialog::on_pBW1_clicked()
{
    if(keep[0]==0)keep[0]=1;
    else keep[0]=0;
}


void singleplayerDialog::on_pBW2_clicked()
{
    if(keep[1]==0)keep[1]=1;
    else keep[1]=0;
}


void singleplayerDialog::on_pBW3_clicked()
{
    if(keep[2]==0)keep[2]=1;
    else keep[2]=0;
}


void singleplayerDialog::on_pBW4_clicked()
{
    if(keep[3]==0)keep[3]=1;
    else keep[3]=0;
}


void singleplayerDialog::on_pBW5_clicked()
{
    if(keep[4]==0)keep[4]=1;
    else keep[4]=0;
}

