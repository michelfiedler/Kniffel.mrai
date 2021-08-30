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
    for(int i=0; i<=data::spieleranzahl+1; i++)     //i läuft von 0 bis Anzahl der Spieler-1 (Variable spieleranzahl ist 0 bei 2 Spielern) für den Index der Spalten
    {
        data::spieler[i].Spielstand = new int [13]; //Ein Spielstand Feld für die Spieler anfordern
        data::spieler[i].reset_Spielstand();

        ui->tW_SpielstandMulti->setHorizontalHeaderItem(i,new QTableWidgetItem(QString(data::spieler[i].mName)));   //Namen der Spieler im Kniffelblatt eintragen
    }

    QObject::connect(this, &spielmodusMultiDialog::wrongCell, this, &spielmodusMultiDialog::chooseNewCell);

    data::wievielterWurf = 0;

    for(int i=0; i<5; i++) keep[i]=0;
    spielmodusMultiDialog::on_pBwuerfeln_clicked();

}

spielmodusMultiDialog::~spielmodusMultiDialog()
{
    delete ui;

    data::wievielterWurf=0;
    data::Zug=0;

    //Dynamisch angeforderten Speicher wieder freigeben
    for(int i=0; i<=data::spieleranzahl+1; i++)
    {
        delete [] data::spieler[i].Spielstand;
        data::spieler[i].Spielstand = NULL;
    }
}

void spielmodusMultiDialog::on_buttonBox_rejected() //Dialog schließen
{
    this->close();
}

/*Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden.
Es werden die Zeilen- und Spaltennummer übergeben.*/
void spielmodusMultiDialog::on_tW_SpielstandMulti_cellClicked(int row, int column)
{
    ui->tW_SpielstandMulti->setSortingEnabled(false);

    if(column==data::welcherSpieler)        //Dafür sorgen, dass der aktuelle Spieler nur in seine Spalte die Punkte eintragen kann
    {
        if(data::spieler[data::welcherSpieler].Spielstand[row] == 888) //Nur Eintragen, wenn Feld unbeschrieben ist
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

            //Um die Spieler am benutzen der Würfel des vorherigen Spielers zu hindern, wird schon einmal gewürfelt
            for(int i=0; i<5; i++) keep[i] = 0;
            spielmodusMultiDialog::on_pBwuerfeln_clicked();

            if (data::Zug==0)
            {
                QMessageBox msgBox;                 //Die Message Box wird erstellt.
                msgBox.setText("Der nächste Spieler ist dran! Es wurde bereits das erste Mal für dich gewürfelt. Gib nach jedem Wurf an, welche Würfel du behalten willst, bevor du neu würfelst!");                             //Es wird dem nächsten Spieler angezeigt, dass er dran ist und bereits für ihn gewürfelt wurde.
                msgBox.exec();                      //Die Message Box signalisiert dem nächsten Spieler, dass er an der Reihe ist.
            }
        }
        else {emit wrongCell();}
    }
    else {emit wrongCell();}


    //Spielende--------------------------------------------------------------------------------------------------------------------------
    //Endpunktzahlen werden berechnet, wenn der letzte Zug erreicht wurde
    if (data::Zug ==13)
    {
        int* Endpunktzahlen = new int [data::spieleranzahl+2];
        int* order = new int [data::spieleranzahl+2];
        for (int i=0; i<data::spieleranzahl+2; i++)
        {
            data::spieler[i].Endpunktzahl = sum(data::spieler[i].Spielstand, 13);
            if(sum(data::spieler[i].Spielstand, 6) > 62) data::spieler[i].Endpunktzahl +=35;
        }
        refreshEndTabelle();
        for(int i=0; i<data::spieleranzahl+2; i++) order[i] = i;
        for(int i=0; i<data::spieleranzahl+2; i++) Endpunktzahlen[i] = data::spieler[i].Endpunktzahl;
        sort(Endpunktzahlen, order, data::spieleranzahl+2); //data::spieler[order[data::spieleranzahl+1] ist der beste Spieler

        //Ausgabe der Punkteauswertung
        int value = data::spieler[order[data::spieleranzahl+1]].Endpunktzahl;
        QString Name = QString (data::spieler[order[data::spieleranzahl+1]].mName);
        //Auszugebener Text
        QString text = QString("Herzlichen Glückwunsch\n %1 , Du hast gewonnen! Mit einer Punktzahl von: %2").arg(Name).arg(value);
        QMessageBox::information(0, "Punkteauswertung", text);

        /*Nun überprüfen, ob die Punkte der Spieler ausreichen, um in die Highscoreliste eingetragen zu werden. Dafür muss der Name, der als QString gespeichert
         *  wurde in char* umgewandelt werden*/
        for (int i=0; i<=data::spieleranzahl+1; i++)
        {
            QString playerName = data::spieler[i].mName;
            char* namePlayer;
            string pname = playerName.toStdString();
            namePlayer = new char [pname.size()+1];
            strcpy( namePlayer, pname.c_str() );

            //Nun überprüfen
            data::bestenliste.fuellenBestenliste(data::spieler[i].Endpunktzahl, namePlayer);
            //Nach Überprüfung des letzten Spielers, Speicher wieder freigeben
            if(i==data::spieleranzahl+1){delete[] namePlayer; namePlayer=NULL;}
        }

        delete[]Endpunktzahlen;
        Endpunktzahlen=NULL;
        delete[]order;
        order=NULL;
    }
}

//Endpunktzahlen werden ins Kniffelgewinnblatt eingetragen
void spielmodusMultiDialog::refreshEndTabelle()
{
    for (int i=0; i<data::spieleranzahl+2; i++)
    {
        ui->tW_SpielstandMulti->setItem(13,i, new QTableWidgetItem(QString::number(data::spieler[i].Endpunktzahl)));
    }
}

//Spieler signalisieren ein anderes Feld im Gewinnblatt auszuwählen
void spielmodusMultiDialog::chooseNewCell()
{
    QMessageBox myMsgBox;
    myMsgBox.setText("Dieses Feld kannst Du nicht beschreiben. Bitte wähle ein anderes aus.");
    myMsgBox.exec();
}

//Button "Würfeln" würfelt und zeigt die Würfelergebnisse in der GUI an
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

        data::wievielterWurf++; //Variable für die Anzahl der Würfe hochsetzen
    }
}

//Wenn die Buttons "behalten" gedrückt werden, soll der Würfel behalten werden->der behalten Button "leuchtet" in dem Fall
void spielmodusMultiDialog::on_pBW1_clicked()
{
    if(ui->pBW1->isChecked())keep[0]=1; //Wenn die Buttons gedrückt werden, soll der Würfel behalten werden->der behalten Button "leuchtet" in dem Fall
    else keep[0]=0;
}


void spielmodusMultiDialog::on_pBW2_clicked()
{
    if(ui->pBW2->isChecked())keep[1]=1;
    else keep[1]=0;
}


void spielmodusMultiDialog::on_pBW3_clicked()
{
    if(ui->pBW3->isChecked())keep[2]=1;
    else keep[2]=0;
}


void spielmodusMultiDialog::on_pBW4_clicked()
{
    if(ui->pBW4->isChecked())keep[3]=1;
    else keep[3]=0;
}


void spielmodusMultiDialog::on_pBW5_clicked()
{
    if(ui->pBW5->isChecked())keep[4]=1;
    else keep[4]=0;
}


















