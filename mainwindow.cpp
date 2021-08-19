#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"

#include <fstream>
#include <string>
#include <sstream>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tBwelcomeText->setStyleSheet("background:transparent;color: rgb(255, 255, 255);");
    ui->lBestenliste->setStyleSheet("background-color: rgb(32, 45, 53);");
    ui->lBestenliste->setStyleSheet("color: rgb(255, 255, 255);");
    ui->tW_Bestenliste->setStyleSheet("background:transparent;");
    ui->pBsingle->setStyleSheet("background-color: rgb (27, 42, 49);");
    ui->pBsingle->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pBsaveScores->setStyleSheet("background-color: rgb (27, 42, 49);");
    ui->pBsaveScores->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pBmulti->setStyleSheet("background-color: rgb (27, 42, 49);");
    ui->pBmulti->setStyleSheet("color: rgb(255, 255, 255);");



    //Bei Programmstart werden aus einer Datei die bisherigen Highscores ausgelesen und in den Variablen gespeichert
    ifstream datei;
    datei.open("bestenlisteSpeichern.conf");
    string line;
    if(datei.is_open())
    {
        while(getline(datei,line))
        {
            for(int i=0; i<line.size(); i++)
            {
                if(line[i] == ' ')
                {
                    line[i] = ',';
                }
            }
            for(int i=0; i<line.size(); i++)
            {
                if(line[i] == ';')
                {
                    line[i] = ' ';
                }
            }
            stringstream linebuffer(line);
            linebuffer>>data::bestenliste.platz1>>data::bestenliste.name1>>data::bestenliste.platz2>>data::bestenliste.name2>>data::bestenliste.platz3>>data::bestenliste.name3
                    >>data::bestenliste.platz4>>data::bestenliste.name4>>data::bestenliste.platz5>>data::bestenliste.name5;
        }
        datei.close();
    }
    fillBestenliste();     //Die Highscoreliste wird mit den ausgelesenen Variablen gefüllt

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


void MainWindow::on_pBmulti_clicked()           //Button Multiplayer wurde ausgewählt und öffnet ein neues Fenster, um im MultiplayerModus zu spielen.
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
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(QString::number(data::bestenliste.platz1)));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(QString(data::bestenliste.name1)));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(QString::number(data::bestenliste.platz2)));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(QString(data::bestenliste.name2)));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(QString::number(data::bestenliste.platz3)));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(QString(data::bestenliste.name3)));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(QString::number(data::bestenliste.platz4)));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(QString(data::bestenliste.name4)));
        ui->tW_Bestenliste->insertRow(ui->tW_Bestenliste->rowCount());
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 0, new QTableWidgetItem(QString::number(data::bestenliste.platz5)));
        ui->tW_Bestenliste->setItem(ui->tW_Bestenliste->rowCount()-1, 1, new QTableWidgetItem(QString(data::bestenliste.name5)));

        for(int i=0; i<5; i++)
        {
            for(int j=0; j<2; j++)
            {
                ui->tW_Bestenliste->item(i,j)->setTextAlignment(Qt::AlignHCenter);
                ui->tW_Bestenliste->item(i,j)->setBackground(QColor(255,255,255));
            }
        }
}



void MainWindow::on_pBsaveScores_clicked()
{
    //Bei Programmende werden die aktuellen Highscores in einer Datei gespeichert
    ofstream file;
    file.open("bestenlisteSpeichern.conf");
    if(file.is_open())
    {
        file<<data::bestenliste.platz1<<';'<<data::bestenliste.name1<<';'<<data::bestenliste.platz2<<';'<<data::bestenliste.name2<<';'<<data::bestenliste.platz3<<';'<<data::bestenliste.name3
           <<';'<<data::bestenliste.platz4<<';'<<data::bestenliste.name4<<';'<<data::bestenliste.platz5<<';'<<data::bestenliste.name5;
        file.close();
    }
}

