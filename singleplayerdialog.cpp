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
    //Hier eine doppelte for-Schleife einfügen, die mithilfe der Kontrollfunktionen die entsprechenden Punkte in das Feld einträgt
}

