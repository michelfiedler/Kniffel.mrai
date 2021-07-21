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

