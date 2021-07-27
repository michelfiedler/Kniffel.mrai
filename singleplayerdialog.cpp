#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"
#include "data.h"
#include "Funktionen.h"
#include "FunktionenKI.h"

#include <QObject>
#include <QMessageBox>
#include <QLCDNumber>
#include <QLabel>
#include <windows.h>

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);


    data::singleSpieler.Spielstand = new int [13]; //Ein Spielstand Feld für den SinglePlayer erstellen
    data::singleSpieler.reset_Spielstand();
    data::KI.Spielstand = new int[13];
    data::KI.reset_Spielstand();
    //for (int i=0; i<13; i++) {data::singleSpieler.Spielstand[i]=0;} //Alle Einträge des Spielstandes auf 0 setzen

    QObject::connect(this, &singleplayerDialog::besetzt, this, &singleplayerDialog::neuWaehlen);    //Der Slot neuWaehlen und das Signal besetzt werden verknüpft
    QObject::connect(this, &singleplayerDialog::KIistdran, this, &singleplayerDialog::KIZug);
    QObject::connect(this, &singleplayerDialog::spielEnde, this, &singleplayerDialog::wertung);

}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
    //Dynamisch angeforderten Speicher wieder freigeben
    delete [] data::singleSpieler.Spielstand;
    data::singleSpieler.Spielstand = NULL;

}

void singleplayerDialog::refreshTable()
{
    for(int i=0; i<13; i++)
    {
        if(data::singleSpieler.Spielstand[i] == 888)
        {
            ui->tW_SpielstandSingle->setItem(i, 0, new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[i])));
        }
        else
        {
            ui->tW_SpielstandSingle->setItem(i, 0, new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[i])));
        }

        if(data::KI.Spielstand[i] == 888)
        {
            ui->tW_SpielstandSingle->setItem(i, 1, new QTableWidgetItem(QString::number(data::KI.Spielstand[i])));
        }
        else
        {
            ui->tW_SpielstandSingle->setItem(i, 1, new QTableWidgetItem(QString::number(data::KI.Spielstand[i])));
        }
    }


    //ui->tW_SpielstandSingle->setItem(order[12-m_temp],1,new QTableWidgetItem(QString::number(data::KI.Spielstand[order[12-m_temp]])));

}


//Slots

void singleplayerDialog::on_buttonBox_rejected()        //Der SingleplayerModus wird geschlossen
{
    this->close();
}

/*void singleplayerDialog::on_tW_SpielstandSingle_cellClicked(int row, int column)    //Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden
{
    ui->tW_SpielstandSingle->setSortingEnabled(false);  //Sortieren der Tabelle abschalten

    if (column!=1)       //Dafür sorgen, dass nur ins Spieler-Feld und nicht ins KI-Feld eingetragen wird
    {
        //Jedes Event beschreibt das Spielstandfeld und setzt den erwünschten Wert aus dem Spielstand in die Tabelle ein
        if (row==0) //Einsen
        {
            if (!(ui->tW_SpielstandSingle->item(0,0))) { write (dice, data::singleSpieler.Spielstand, 1); //Testen, ob schon ein Item existiert und wenn nicht, den Spielstand beschreiben
                QTableWidgetItem *item= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[0])); //ein Item für die Tabelle erstellen und den Eintrag in einen integer umwandeln, um die Punkte des Spielstandes einzutragen
                ui->tW_SpielstandSingle->setItem(0,0, item);
                emit KIistdran();
            } //Das Item in die Tabelle einfügen
            else {emit besetzt();}            //Signal für erneute Feldauswahl, falls in diesem Feld schon Punkte eingetragen wurden

        }
        else if (row==1) //Zweien
        {
            if (!(ui->tW_SpielstandSingle->item(1,0))) {write (dice, data::singleSpieler.Spielstand, 2);
                QTableWidgetItem *item1= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[1]));
                ui->tW_SpielstandSingle->setItem (1,0,item1);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==2) //Dreien
        {
            if (!(ui->tW_SpielstandSingle->item(2,0))) {write (dice, data::singleSpieler.Spielstand, 3);
                QTableWidgetItem *item2= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[2]));
                ui->tW_SpielstandSingle->setItem (2,0,item2);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==3) //Vieren
        {
            if (!(ui->tW_SpielstandSingle->item(3,0))) {write (dice, data::singleSpieler.Spielstand, 4);
                QTableWidgetItem *item3= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[3]));
                ui->tW_SpielstandSingle->setItem (3,0,item3);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==4)//Fünfen
        {
            if (!(ui->tW_SpielstandSingle->item(4,0))) {write (dice, data::singleSpieler.Spielstand, 5);
                QTableWidgetItem *item4= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[4]));
                ui->tW_SpielstandSingle->setItem (4,0,item4);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==5) //Sechsen
        {
            if (!(ui->tW_SpielstandSingle->item(5,0))) {write (dice, data::singleSpieler.Spielstand, 6);
                QTableWidgetItem *item5= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[5]));
                ui->tW_SpielstandSingle->setItem (5,0,item5);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==6) //Dreierpasch
        {
            if (!(ui->tW_SpielstandSingle->item(6,0))) {write (dice, data::singleSpieler.Spielstand, 7);
                QTableWidgetItem *item6= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[6]));
                ui->tW_SpielstandSingle->setItem(6,0,item6);
                emit KIistdran();
            }
            else {emit besetzt();}

        }
        else if (row==7) //Viererpasch
        {
            if (!(ui->tW_SpielstandSingle->item(7,0))) {write (dice, data::singleSpieler.Spielstand, 8);
                QTableWidgetItem *item7= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[7]));
                ui->tW_SpielstandSingle->setItem(7,0,item7);
                emit KIistdran();
            }
            else {emit besetzt();}
        }
        else if (row==8) //FullHouse
        {
           if (!(ui->tW_SpielstandSingle->item(8,0))) {write (dice, data::singleSpieler.Spielstand, 9);
               QTableWidgetItem *item8= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[8]));
                ui->tW_SpielstandSingle->setItem(8,0,item8);
            emit KIistdran();
           }
           else {emit besetzt();}
        }
        else if (row==9) //kl Strasse
        {
            if (!(ui->tW_SpielstandSingle->item(9,0))) {write (dice, data::singleSpieler.Spielstand, 10);
                QTableWidgetItem *item9= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[9]));
                ui->tW_SpielstandSingle->setItem(9,0,item9);
                emit KIistdran();
            }
            else {emit besetzt();}
        }
        else if (row==10) //gr Strasse
        {
            if (!(ui->tW_SpielstandSingle->item(10,0))) {write (dice, data::singleSpieler.Spielstand, 11);
                QTableWidgetItem *item10= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[10]));
                ui->tW_SpielstandSingle->setItem(10,0,item10);
                emit KIistdran();
            }
            else {emit besetzt();}
        }
        else if (row==11) //Kniffel
        {
            if (!(ui->tW_SpielstandSingle->item(11,0))) {write (dice, data::singleSpieler.Spielstand, 12);
                QTableWidgetItem *item11= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[11]));
                ui->tW_SpielstandSingle->setItem(11,0,item11);
                emit KIistdran();
            }
            else {emit besetzt();}
        }
        else if (row==12) //Chance
        {
            if (!(ui->tW_SpielstandSingle->item(12,0))) {write (dice, data::singleSpieler.Spielstand, 13);
                QTableWidgetItem *item12= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[12]));
                ui->tW_SpielstandSingle->setItem(12,0,item12);
                emit KIistdran();
            }
            else {emit besetzt();}
        }
    }
    else {emit besetzt();}        //Signal für erneute Feldauswahl

}*/



void singleplayerDialog::on_tW_SpielstandSingle_cellClicked(int row, int column)    //Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden
{
    ui->tW_SpielstandSingle->setSortingEnabled(false);  //Sortieren der Tabelle abschalten

    if (column!=1)       //Dafür sorgen, dass nur ins Spieler-Feld und nicht ins KI-Feld eingetragen wird
    {
        if (data::singleSpieler.Spielstand[row] == 888) { write (dice, data::singleSpieler.Spielstand, row+1); //Testen, ob schon ein Item existiert und wenn nicht, den Spielstand beschreiben
            QTableWidgetItem *item= new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[row])); //ein Item für die Tabelle erstellen und den Eintrag in einen integer umwandeln, um die Punkte des Spielstandes einzutragen
            ui->tW_SpielstandSingle->setItem(row,0, item);
            emit KIistdran();
        } //Das Item in die Tabelle einfügen
        else {emit besetzt();}            //Signal für erneute Feldauswahl, falls in diesem Feld schon Punkte eingetragen wurden
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

void singleplayerDialog::KIZug()
{

    double* Erwartungswerte = new double[13];
    int* EintragTemp = new int[13];
    int* order = new int[13];
    int m_temp = 0;

    cout<<endl<<"testtestTESTTESTTESTTEST"<<endl<<endl<<endl;

    //Variablen für die Bilder der Würfel anlegen
    QPixmap KIaugen1 (":/MyImages/imageWuerfel1.png");
    QPixmap KIaugen2 (":/MyImages/imageWuerfel2.png");
    QPixmap KIaugen3 (":/MyImages/imageWuerfel3.png");
    QPixmap KIaugen4 (":/MyImages/imageWuerfel4.png");
    QPixmap KIaugen5 (":/MyImages/imageWuerfel5.png");
    QPixmap KIaugen6 (":/MyImages/imageWuerfel6.png");

        for (int i=0; i<5; i++) {keep[i]=0;}            // Beschreibt das Würfelbehaltenfeld mit Nullen
        for (int Wurf=0; Wurf<3; Wurf++)                         // Nun beginnen die drei Würfe pro Spieler
        {

            rolldice(dice, keep);

            //Für den gewürfelten Wert von Würfel 1 das entsprechende Bild einfügen
            if(dice[0]==1) {ui->qlW1->setPixmap(KIaugen1);}
            if(dice[0]==2) {ui->qlW1->setPixmap(KIaugen2);}
            if(dice[0]==3) {ui->qlW1->setPixmap(KIaugen3);}
            if(dice[0]==4) {ui->qlW1->setPixmap(KIaugen4);}
            if(dice[0]==5) {ui->qlW1->setPixmap(KIaugen5);}
            if(dice[0]==6) {ui->qlW1->setPixmap(KIaugen6);}

            //Für den gewürfelten Wert von Würfel 2 das entsprechende Bild einfügen
            if(dice[1]==1) {ui->qlW2->setPixmap(KIaugen1);}
            if(dice[1]==2) {ui->qlW2->setPixmap(KIaugen2);}
            if(dice[1]==3) {ui->qlW2->setPixmap(KIaugen3);}
            if(dice[1]==4) {ui->qlW2->setPixmap(KIaugen4);}
            if(dice[1]==5) {ui->qlW2->setPixmap(KIaugen5);}
            if(dice[1]==6) {ui->qlW2->setPixmap(KIaugen6);}

            //Für den gewürfelten Wert von Würfel 3 das entsprechende Bild einfügen
            if(dice[2]==1) {ui->qlW3->setPixmap(KIaugen1);}
            if(dice[2]==2) {ui->qlW3->setPixmap(KIaugen2);}
            if(dice[2]==3) {ui->qlW3->setPixmap(KIaugen3);}
            if(dice[2]==4) {ui->qlW3->setPixmap(KIaugen4);}
            if(dice[2]==5) {ui->qlW3->setPixmap(KIaugen5);}
            if(dice[2]==6) {ui->qlW3->setPixmap(KIaugen6);}

            //Für den gewürfelten Wert von Würfel 4 das entsprechende Bild einfügen
            if(dice[3]==1) {ui->qlW4->setPixmap(KIaugen1);}
            if(dice[3]==2) {ui->qlW4->setPixmap(KIaugen2);}
            if(dice[3]==3) {ui->qlW4->setPixmap(KIaugen3);}
            if(dice[3]==4) {ui->qlW4->setPixmap(KIaugen4);}
            if(dice[3]==5) {ui->qlW4->setPixmap(KIaugen5);}
            if(dice[3]==6) {ui->qlW4->setPixmap(KIaugen6);}

            //Für den gewürfelten Wert von Würfel 5 das entsprechende Bild einfügen
            if(dice[4]==1) {ui->qlW5->setPixmap(KIaugen1);}
            if(dice[4]==2) {ui->qlW5->setPixmap(KIaugen2);}
            if(dice[4]==3) {ui->qlW5->setPixmap(KIaugen3);}
            if(dice[4]==4) {ui->qlW5->setPixmap(KIaugen4);}
            if(dice[4]==5) {ui->qlW5->setPixmap(KIaugen5);}
            if(dice[4]==6) {ui->qlW5->setPixmap(KIaugen6);}

            //Sleep(3000);


            for (int i=0; i<5; i++) {keep[i]=0;}            //??? unsicher: muss das keep feld genau hier hin??
            //----------------------------------------------------------------------------------------------------------------------------------------------
            //Erster Wurf der KI

            if(Wurf==0)
            {
                Erwartungswerte[0] = ErwartungswertOben1(dice, 1);
                Erwartungswerte[1] = ErwartungswertOben1(dice, 2);
                Erwartungswerte[2] = ErwartungswertOben1(dice, 3);
                Erwartungswerte[3] = ErwartungswertOben1(dice, 4);
                Erwartungswerte[4] = ErwartungswertOben1(dice, 5);
                Erwartungswerte[5] = ErwartungswertOben1(dice, 6);
                Erwartungswerte[6] = ErwartungswertDreierPasch1(dice);
                Erwartungswerte[7] = ErwartungswertViererPasch1(dice);
                Erwartungswerte[8] = ErwartungswertFullhouse1(dice);
                Erwartungswerte[9] = ErwartungswertklStrasse1(dice);
                Erwartungswerte[10]= ErwartungswertgrStrasse1(dice);
                Erwartungswerte[11]= ErwartungswertKniffel1(dice);
                Erwartungswerte[12]= 0;                                 //Chance

                sort(Erwartungswerte, order, 13);                   //Erwartungswerte[order[12]] ist der höchste, [0] der kleinste Eintrag

                for (int i=0; i<13; i++)
                {
                    if (data::KI.Spielstand[order[12-i]] == 888)
                    {
                        m_temp = i;
                        setGoal(dice, keep, order[12-i], 0);
                        //Ereignis mit dem höchsten Erwartungswert ist noch nicht belegt, es wird als Ziel für den nächsten Wurf gewählt
                        i = 13;
                    }
                }
            }

            //--------------------------------------------------------------------------------------------------------------------------------------------
            //Zweiter Wurf der KI

            if(Wurf==1)
            {
                Erwartungswerte[0] = ErwartungswertOben2(dice, 1);
                Erwartungswerte[1] = ErwartungswertOben2(dice, 2);
                Erwartungswerte[2] = ErwartungswertOben2(dice, 3);
                Erwartungswerte[3] = ErwartungswertOben2(dice, 4);
                Erwartungswerte[4] = ErwartungswertOben2(dice, 5);
                Erwartungswerte[5] = ErwartungswertOben2(dice, 6);
                Erwartungswerte[6] = ErwartungswertDreierPasch2(dice);
                Erwartungswerte[7] = ErwartungswertViererPasch2(dice);
                Erwartungswerte[8] = ErwartungswertFullhouse2(dice);
                Erwartungswerte[9] = ErwartungswertklStrasse2(dice);
                Erwartungswerte[10]= ErwartungswertgrStrasse2(dice);
                Erwartungswerte[11]= ErwartungswertKniffel2(dice);
                Erwartungswerte[12]= 0;                                 //Chance

                sort(Erwartungswerte, order, 13);                   //Erwartungswerte[order[12]] ist der höchste, [0] der kleinste Eintrag

                for (int i=0; i<13; i++)
                {
                    if (data::KI.Spielstand[order[12-i]] == 888)
                    {
                        m_temp = i;
                        setGoal(dice, keep, order[12-i], 1);

                        //Ereignis mit dem höchsten Erwartungswert ist noch nicht belegt, es wird als Ziel für den nächsten Wurf gewählt
                        i = 13;
                    }
                }
            }


            //Vorzeitig ein Ziel erreicht --------------------------------------------------------------------------------------------------------------------
            if((Wurf==0||Wurf==1)&&keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
            {
                write(dice, data::KI.Spielstand, order[12-m_temp]+1);
                ui->tW_SpielstandSingle->setItem(order[12-m_temp],1,new QTableWidgetItem(QString::number(data::KI.Spielstand[order[12-m_temp]])));

                Wurf=3;										//Für Schleifenabbruch sorgen, da alle Wuerfel behalten werden
            }
            //Nach dem dritten Wurf --------------------------------------------------------------------------------------------------------------------------
            if(Wurf==2)
            {
                for (int i=0; i<13; i++)
                {
                    write(dice, EintragTemp, i+1);
                }
                EintragTemp[12] = 0;
                for(int i=0; i<3; i++) EintragTemp[i]+=9; //Kniffelbonus wird höher gewichtet!
                for(int i=3; i<6; i++) EintragTemp[i]+=7; //damit nicht einer der Päsche eingetragen wird.
                sort(EintragTemp, order, 13);

                /*  Die Funktion EintragLetzterWurf trägt den möglicherweise besten Wert ein und gibt true zurück, falls ein wert eingrtragen wurde.
                 *  Da Sie Funktion viele if-Schaltungen enthält, laufen die Abfragen in wenigen Spezialfällen ins Leere und es kann vorkommen,
                 *  dass kein Wert ins Gewinnblatt eingetragen wird. Um diesen Bug zu verhindern, wird abgefragt, ob etwas eingetragen wurde. Falls nicht,
                 *  soll einfach das ereignis mit dem H´höchstmöglichen Wert eingetragen werden.
                 *      ÜBRIGENS: Das Ereignis mit dem höchstmöclichen Wert ist NICHT immer automatisch die beste Wahl, da es dadurch möglicherweise
                 *      nicht mehr möglich ist, den Bonus zu erhalten!
                 */
                if(!EintragLetzterWurf(data::KI.Spielstand, order, dice, data::Zug))
                {
                    for (int i=0; i<13; i++)
                    {
                        if (data::KI.Spielstand[order[12-i]] == 888) //Prüfen, ob Feld noch unbeschrieben
                        {
                            write(dice, data::KI.Spielstand, order[12-i]+1);
                            i = 13;
                            ui->tW_SpielstandSingle->setItem(order[12-i],1,new QTableWidgetItem(QString::number(data::KI.Spielstand[order[12-i]])));

                        }
                    }
                }


              }

            }
        data::Zug++;
        refreshTable();

        for(int i=0; i<5; i++) keep[i] = 0;
        singleplayerDialog::on_pBwuerfeln_clicked();
        if(data::Zug==13) {emit spielEnde();}   //Signal für das Ende des Spiels aussenden


        delete[] Erwartungswerte;
        Erwartungswerte = NULL;
        delete[] EintragTemp;
        EintragTemp = NULL;


}

void singleplayerDialog::wertung()  //Dialog Punkteauswertung öffnen
{
    wertungDialog* wertung= new wertungDialog(this);
    wertung->exec();
}
