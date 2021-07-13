#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"
#include "data.h"

#include <QObject>
#include <QMessageBox>

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);

    QObject::connect(this, &singleplayerDialog::besetzt, this, &singleplayerDialog::neuWaehlen);    //Der Slot neuWaehlen und das Signal besetzt werden verküpft
}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
}

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

void neuWaehlen()   //Slot, der MessageBox anzeigt, welche den Benutzer auffordert ein neues Feld zu wählen
{
    QMessageBox msgBox;
    msgBox.setText("Dieses Feld kann nicht beschrieben werden. Bitte wählen Sie ein anderes aus.");
    msgBox.exec();
}
