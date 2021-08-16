#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"
#include "data.h"
#include "Funktionen.h"
#include "FunktionenKI.h"

#include <QObject>
#include <QMessageBox>
#include <QLCDNumber>
#include <QLabel>
//#include <windows.h>

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
    QObject::connect(this, &singleplayerDialog::SiegDu, this, &singleplayerDialog::wertung);
    QObject::connect(this, &singleplayerDialog::SiegKI, this, &singleplayerDialog::wertung2);
}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
    //Dynamisch angeforderten Speicher wieder freigeben
    delete [] data::singleSpieler.Spielstand;
    data::singleSpieler.Spielstand = NULL;

}

void singleplayerDialog::wertung()  //Dialog Punkteauswertung öffnen, abhängig vom Sieger
{
    wertungDialog* wertung= new wertungDialog(this);
    wertung->exec();
}

void singleplayerDialog::wertung2()
{
    wertung2dialog* wertung2= new wertung2dialog(this);
    wertung2->exec();
}

void singleplayerDialog::refreshTable()
{
    for(int i=0; i<13; i++)
    {
        if(data::singleSpieler.Spielstand[i] != 888)
        {
            ui->tW_SpielstandSingle->setItem(i, 0, new QTableWidgetItem(QString::number(data::singleSpieler.Spielstand[i])));
        }

        if(data::KI.Spielstand[i] != 888)
        {
            ui->tW_SpielstandSingle->setItem(i, 1, new QTableWidgetItem(QString::number(data::KI.Spielstand[i])));
        }
    }


    //ui->tW_SpielstandSingle->setItem(order[12-m_temp],1,new QTableWidgetItem(QString::number(data::KI.Spielstand[order[12-m_temp]])));

}

void singleplayerDialog::refreshEndTabelle()
{
    ui->tW_SpielstandSingle->setItem(13, 0, new QTableWidgetItem(QString::number(data::singleSpieler.Endpunktzahl)));
    ui->tW_SpielstandSingle->setItem(13, 1, new QTableWidgetItem(QString::number(data::KI.Endpunktzahl)));

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
    msgBox.setText("Dieses Feld kann nicht beschrieben werden. Bitte wähle ein anderes aus.");
    msgBox.exec();
}


void singleplayerDialog::on_pBwuerfeln_clicked()    //Würfelt und zeigt die Würfelergebnisse an
{
    ui->pBW1->setChecked(false);    //Die Buttons für das Behalten werden zurückgesetzt->sie "leuchten" nicht mehr
    ui->pBW2->setChecked(false);
    ui->pBW3->setChecked(false);
    ui->pBW4->setChecked(false);
    ui->pBW5->setChecked(false);
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

//NUN IST DIE KI DRAN!
void singleplayerDialog::KIZug()
{

    double* Erwartungswerte = new double[13];
    int* EintragTemp = new int[13];
    int* order = new int[13];
    int m_temp = 0;

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

            //Bildschirmausganbe, um Aktionen zu prüfen
                    cout<<"WUERFEL"<<endl;
                    for(int i=0; i<5; i++) cout<<dice[i]<<"   ";
                    cout<<endl;

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


            for (int i=0; i<5; i++) {keep[i]=0;} //Das Würfelbehaltenfeld wird erneut mit Nullen beschrieben!
            //----------------------------------------------------------------------------------------------------------------------------------------------
            //Erster Wurf der KI

            if(Wurf==0)
            {
                cout<<"NACH ERSTEM WURF"<<endl;

                //Berechnen der Erwartungswerte mit der jeweiligen Funktion nach dem ersten Wurf
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

                //Bildschirmausganbe, um Aktionen zu prüfen
                        cout<<"ERWARTUNGSWERTE und REIHENFOLGE"<<endl;
                        for(int i=0; i<13; i++) cout<<i<<": "<<Erwartungswerte[i]<<"               "<<order[i]<<endl;
                        cout<<endl;

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

                cout<<"Ziel: "<<order[12-m_temp]<<endl;
                for(int i=0; i<5; i++)cout<<keep[i]<<"   ";
                cout<<endl;
            }

            //--------------------------------------------------------------------------------------------------------------------------------------------
            //Zweiter Wurf der KI

            if(Wurf==1)
            {
                cout<<"NACH ZWEITEM WURF"<<endl;

                //Berechnen der Erwartungswerte mit den jeweiligen Funktionen nach dem zweiten Wurf
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

                //Bildschirmausganbe, um Aktionen zu prüfen
                        cout<<"ERWARTUNGSWERTE und REIHENFOLGE"<<endl;
                        for(int i=0; i<13; i++) cout<<i<<": "<<Erwartungswerte[i]<<"               "<<order[i]<<endl;
                        cout<<endl;

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
                cout<<"Ziel: "<<order[12-m_temp]<<endl;
                for(int i=0; i<5; i++)cout<<keep[i]<<"   ";
                cout<<endl;
            }


            //Vorzeitig ein Ziel erreicht --------------------------------------------------------------------------------------------------------------------
            if((Wurf==0||Wurf==1)&&keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
            {
                //Eintragen des ermittelten Ereignisses ins Kniffel-Gewinnblatt
                write(dice, data::KI.Spielstand, order[12-m_temp]+1);
                ui->tW_SpielstandSingle->setItem(order[12-m_temp],1,new QTableWidgetItem(QString::number(data::KI.Spielstand[order[12-m_temp]])));

                cout<<order[12-m_temp]<<" eingetragen"<<endl;

                Wurf=3;										//Für Schleifenabbruch sorgen, da alle Wuerfel behalten werden
            }
            //Nach dem dritten Wurf --------------------------------------------------------------------------------------------------------------------------
            if(Wurf==2)
            {
                cout<<"NACH DRITTEM WURF"<<endl;

                for (int i=0; i<13; i++)
                {
                    write(dice, EintragTemp, i+1);
                }
                EintragTemp[12] = 0;
                for(int i=0; i<3; i++) EintragTemp[i]+=9; //Kniffelbonus wird höher gewichtet!
                for(int i=3; i<6; i++) EintragTemp[i]+=7; //Bevorzugtes Eintragen in den oberen Zahlenblock anstatt einen der Päsche einzugetragen.
                sort(EintragTemp, order, 13);

                //Bildschirmausganbe, um Aktionen zu prüfen
                        cout<<"TEMP-EINTRÄGE und REIHENFOLGE"<<endl;
                        for(int i=0; i<13; i++) cout<<i<<": "<<EintragTemp[i]<<"               "<<order[12-i]<<endl;
                        cout<<endl;

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

                            cout<<order[12-i]<<" eingetragen"<<endl;

                        }
                    }
                }


              }

            }
        data::Zug++; //Nun ist der erste Zug durchgeführt und die Zugvariable wird um eins erhöht
        refreshTable(); //Das Kniffel-Gewinnblatt wird aktualisiert

        //Die folgende Schleife dient dazu, dass der Singlespieler die Würfel der KI nicht mehr für sich eintragen kann.
        for(int i=0; i<5; i++) keep[i] = 0;
        singleplayerDialog::on_pBwuerfeln_clicked();

        //Spielende---------------------------------------------------------------------------------------------------------------------------------------------------
        if(data::Zug==13)
        {
            //Endpunktzahlen berechnen
            data::KI.Endpunktzahl = sum(data::KI.Spielstand, 13);
            if(sum(data::KI.Spielstand, 6) > 62) data::KI.Endpunktzahl +=35;
            data::singleSpieler.Endpunktzahl = sum(data::singleSpieler.Spielstand, 13);
            if(sum(data::singleSpieler.Spielstand, 6) > 62) data::singleSpieler.Endpunktzahl +=35;

            //Endpunktzahlen werden in die Tabelle miteingefügt
            refreshEndTabelle();

            //Ausgabe des Sieges oder der Niederlage
            if (data::singleSpieler.Endpunktzahl>data::KI.Endpunktzahl)
            {

                emit SiegDu();  //Signal für den Sieg des Singlespielers aussenden
            }
            else
            {
                emit SiegKI();
            }
        }


        delete[] Erwartungswerte;
        Erwartungswerte = NULL;
        delete[] EintragTemp;
        EintragTemp = NULL;


}





void singleplayerDialog::on_nameSpeichern_clicked()
{
    data::singleSpieler.mName = ui ->singleName->text().trimmed();              //Der eingegebene Name des Spieler wird für die Bestenliste gespeichert.
    QMessageBox msgBox;
    msgBox.setText("Dein Name wurde gespeichert!");                             //Der Spieler erhält durch die MessageBox die Information , dass sein Name gespeichert wurde.
    msgBox.exec();

}

