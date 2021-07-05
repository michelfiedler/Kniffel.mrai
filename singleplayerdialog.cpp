#include "singleplayerdialog.h"
#include "ui_singleplayerdialog.h"

singleplayerDialog::singleplayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singleplayerDialog)
{
    ui->setupUi(this);
}

singleplayerDialog::~singleplayerDialog()
{
    delete ui;
}

void singleplayerDialog::on_buttonBox_rejected()        //Der SingleplayerModus wird geschlossen ohne die Daten zu speichern
{
    this->close();
}


void singleplayerDialog::on_tW_SpielstandSingle_cellClicked(int row, int column)    //Wenn ein besetimmtes Feld im Gewinnblatt geklickt wird, soll der entsprechende Spielstand eingetragen werden
{
    //Hier if-Schleifen einfügen, die mithilfe der Kontrollfunktionen die entsprechenden Punkte in das Feld einträgt und in dem Fall, dass der Eintrag nicht möglich ist ein Signal sendet,
    //dass schlussendlich ein Fenster öffnet und den Benutzer bittet ein anderes Feld anzuklicken (mit OK schließen)
    //Wenn das Feld beschrieben werden kann, wird erst die write funktion aufgerufen und dort das zugehörige Feld beschrieben mit den Punkten und dann hier einfach nur noch der entsprechende Feldzeiger aufgerufen
}

