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

