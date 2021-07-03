#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bestenliste.h"
#include "spieler.h"

#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBeenden_triggered()    //Das Programm "Kniffel" wird geschlossen
{
    this->close();
}


void MainWindow::on_pBsingle_clicked()          //Button Singleplayer wurde ausgewählt
{

}


void MainWindow::on_pBmulti_clicked()           //Button Multiplayer wurde ausgewählt
{

}


void MainWindow::on_pB_Bestenliste_clicked()    //Button, um die Bestenliste anzuzeigen
{
    int num;
    int count=0;
    string line;

    //Die Datei öffnen und die Zeilen zählen

    ifstream bestenlisteLesenFile1;
    bestenlisteLesenFile1.open("Bestenliste.conf");
    while (getline(bestenlisteLesenFile1, line))
        count++;
    bestenlisteLesenFile1.close();

    //Die Datei auslesen Zeile um Zeile

    ifstream bestenlisteLesenFile2;
    bestenlisteLesenFile2.open("Bestenliste.conf");
    if (bestenlisteLesenFile2.is_open())
    {
        string sLine;

        int i=0;
        vector<person> people(count);                               //Vector mit Struct-Einträgen (erstmal leer)

        while(getline(bestenlisteLesenFile2, sLine))
        {
            string delimiter = ":";
            string punkte = sLine.substr(0,sLine.find(delimiter));  //Lesen bis zum Doppelpunkt für die Punktzahl
            string name = sLine.substr(sLine.find(delimiter)+1);    //Danach ist alles der Name

            stringstream ss;
            ss << punkte;
            ss >> num;          //String to Int

            people[i].name = name;      //Befüllen des structs mit den Namen
            people[i].punkte = num;     //Befüllen des structs mit den Punkten
            i = i+1;
        }

        bestenlisteLesenFile2.close();

        sort (people.begin(), people.end(),                         //Sort Algorithmus --> die Liste sortieren
              [] (const person &left, const person &right)
        {return (left.punkte > right.punkte);});

        int anzahlEintraege = people.size();                        //Länge des Struct-Vektors
        for (int i=0; i<anzahlEintraege; i++)
        {
            cout << people[i].name << "\t\t" << people[i].punkte << endl;       //Print der Einträge
        }

    }
}

