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

}

