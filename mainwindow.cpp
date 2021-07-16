#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"

#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillBestenliste();      //Die Bestenliste wird bei Programmstart gefüllt

    QObject::connect(&data::bestenliste, &Bestenliste::UpdateBestenliste, this, &MainWindow::fillBestenliste);  //Der Slot fillBestenliste und das Signal, dass die
}                                                                                                               //Bestenliste verändert wurde, werden verknüpft


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBeenden_triggered()    //Das Programm "Kniffel" wird geschlossen
{
    this->close();
}


void MainWindow::on_pBsingle_clicked()          //Button Singleplayer wurde ausgewählt und öffnet ein neues Fenster, um im SingleplayerModus zu spielen
{
    singleplayerDialog* singleDialog = new singleplayerDialog (this);
    singleDialog->exec();
    data::Spielmodus=0;     //Spielmodus als SinglePlayer festlegen
}


void MainWindow::on_pBmulti_clicked()           //Button Multiplayer wurde ausgewählt
{
        MultiplayerDialog* multiplayerDialog = new MultiplayerDialog(this);
        multiplayerDialog->show();
        data::Spielmodus=1;     //Spielmodus Multiplayer festlegen
}


void MainWindow::fillBestenliste()
{
    ui->tW_Bestenliste->setRowCount(0); //Bisherige Einträge der Bestenliste werden gelöscht

        //Nun wird immer eine Zeile zur Bestenliste hinzugefügt und darin in Absteigender Reihenfolge die Punkte und Namen der Plätze 1 bis 5 eingefügt
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(data::bestenliste.platz1));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(data::bestenliste.name1));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(data::bestenliste.platz2));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(data::bestenliste.name2));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(data::bestenliste.platz3));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(data::bestenliste.name3));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(data::bestenliste.platz4));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(data::bestenliste.name4));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(data::bestenliste.platz5));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(data::bestenliste.name5));
}

