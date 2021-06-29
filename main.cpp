#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <QApplication>

#include "mainwindow.h"
#include "Funktionen.h"
#include "spieler.h"
#include "bestenliste.h"

using namespace std;



int main()
{
    srand((unsigned)time(NULL));                //Zufallsfunktion wird mit time initialiesiert

    int* dice = new int[5];						//dice gibt die Würfelergebnisse an
    for (int i=0; i<5; i++) dice[i]=1;
    int* keep = new int[5];					//keep gibt an, welche Würfel behalten werden sollen
    int Spielmodus;
    int Spieleranzahl;
    int anzeige=0;


    cout 	<<"Willkommen, hier kannst du mit dir selbst Kniffel spielen. Die KI folgt bald."<<endl
            <<"Du kannst zwischendurch waehlen, ob du den Spielstand ansehen willst (1/0). Jetzt kanns losgehen!"<<endl<<endl;


    //Abfrage Single- oder Multiplayer
    cout << "Moechtest du im [0]Single- oder [1]Multiplayermodus spielen?" << endl;
    cin >> Spielmodus;

    if (Spielmodus == 0)
    {
        cout << "Die KI kommt bald!" << endl;
    }

    // ----------------------------------------------------------------------------------------------------------------------------------------------
    // Beginn Multiplayer

        if (Spielmodus == 1)
        {

        //Objektinstanzierung
        do
        {
            cout << "Wie viele Spieler seid ihr?" << endl;
            cin >> Spieleranzahl;
        }
        while(Spieleranzahl<2 || Spieleranzahl>7);


        // Speicheranforderung
        Spieler* spielerptr = new Spieler[Spieleranzahl];


        // Spielerinitialisierung ------------------- Namen eingeben und Spielstände setzen
        char Name[15];
        for (int i=0; i<Spieleranzahl; i++)
        {
            cout << "Bitte gebt eure Namen ein:" << endl;
            cin >> Name;
            spielerptr[i].set_Name(Name);
            spielerptr[i].Spielstand = new int [13];
            spielerptr[i].reset_Spielstand();
        }




    // ----------------------------------------------------------------------------------------------------------------------------------------------
    //Programmablauf

    for (int i=0; i<13; i++) //Durchlauf der 13 Spielzüge
    {
           for (int l=0; l<Spieleranzahl; l++) //Durchlauf der einzelnen Spieler
           {
                cout << "Nun ist:   " << spielerptr[l].get_Name() << "   an der Reihe" << endl;

                                                    //Es wird gefragt, ob der Spielstand angezeigt werden soll und kontrolliert ob die Eingabe korrekt war

            cout <<"Spielstand anzeigen? ";
            cin >> anzeige;
            while (anzeige != 1 && anzeige !=0)
            {
                cout << "Bitte 1 (Spielstand anzeigen) oder 0 (gleich wuerfeln) eingeben." ;
                cin >> anzeige;
            }
            if (anzeige)
            {
                cout << "\nSpieler          ";
                for (int i=0; i<Spieleranzahl+1; i++)
                {
                    cout << "     "<< spielerptr[i].get_Name();
                }
                cout << endl;

                cout <<"\n1 Einsen       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     " << spielerptr[a].getSpielstand(0);
                }
                cout << endl;

                cout <<"\n2 Zweien       ";
                for (int b=0; b<Spieleranzahl; b++)
                {
                    cout <<"     "<< spielerptr[b].getSpielstand(1);
                }
                cout << endl;

                cout <<"\n3 Dreien       ";
                for (int c=0; c<Spieleranzahl; c++)
                {
                    cout <<"     "<< spielerptr[c].getSpielstand(2);
                }
                cout << endl;

                cout <<"\n1 Vieren       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(3);
                }
                cout << endl;

                cout <<"\n1 Fünfen       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(4);
                }
                cout << endl;

                cout <<"\n1 Sechsen       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(5);
                }
                cout << endl;

                cout <<"\n1 Dreierpasch       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<<spielerptr[a].getSpielstand(6);
                }
                cout << endl;

                cout <<"\n1 Viererpasch       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(7);
                }
                cout << endl;

                cout <<"\n1 Full House      ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(8);
                }
                cout << endl;

                cout <<"\n1 kl Strasse      ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(9);
                }
                cout << endl;

                cout <<"\n1 gr Strasse       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(10);
                }
                cout << endl;

                cout <<"\n1 Kniffel       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(11);
                }
                cout << endl;

                cout <<"\n1 Chance       ";
                for (int a=0; a<Spieleranzahl; a++)
                {
                    cout <<"     "<< spielerptr[a].getSpielstand(12);
                }
                cout << endl;
            }

            //Hier wird gewürfelt
            for (int j=0; j<5; j++) {keep[j]=0;}            //Das keep-Feld wird resetet
            for (int j=0; j<3; j++)                         //Nun beginnen die drei Würfe pro Spielzug
            {
                rolldice(dice, keep);
                if(j==0||j==1)                              //Im ersten und zweiten Zug kann ausgewählt werden, welche Würfel behalten werden
                {
                    cout <<"\ngewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                    cout <<"behalten? (1/0)	"; for(int k=0; k<5; k++) {cin >>keep[k]; cout<<"   ";}cout<<endl;
				
                    if(keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
                        {
                            write(dice, spielerptr[l].Spielstand);
                            j=3;										//Für Schleifenabbruch sorgen, wenn vor dem dritten Wurf alle Würfel behalten werden
                        }
				
                }
                else                            //Im dritten Zug wird direkt etwas eingetragen
                {
				cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                write(dice, spielerptr[l].Spielstand);
                }
            }
           }

    }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Punkteauswertung

    Punkteauswertung(Spieleranzahl,spielerptr);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Bestenliste

        int num;
        int count=0;
        string line;

        ofstream bestenlisteFile;                                       //Erstellen einer Datei für die Bestenliste
        bestenlisteFile.open ("Bestenliste.conf", ios::app);
        for (int i=0; i<Spieleranzahl; i++)                             //Die Spieler mit ihrer Punktzahl in die Bestenliste einschreiben
        {
             bestenlisteFile << spielerptr[i].Endpunktzahl << ":    " << spielerptr[i].get_Name() << endl;

        }
        bestenlisteFile.close();

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

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Speicherfreigabe
    
    delete[] dice;
    dice = NULL;
    delete[] keep;
    keep = NULL;
    delete[] spielerptr;
    spielerptr = NULL;

    return 0;

}
}
