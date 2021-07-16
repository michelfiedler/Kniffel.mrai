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
#include "FunktionenKI.h"
#include "data.h"

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);                 //MainWindow wird initialisiert und geöffnet
    MainWindow w;
    w.show();
    return a.exec();

    srand((unsigned)time(NULL));                //Zufallsfunktion wird mit time initialiesiert

    //int* dice = new int[5];						//wurde schon in funktionen.cpp definiert
    for (int i=0; i<5; i++) dice[i]=1;              //alle Würfel werden auf 1 gesetzt
    int* keep = new int[5];					//keep gibt an, welche Würfel behalten werden sollen
    int Spielmodus;
    int Spieleranzahl;
    int anzeige=0;


    cout 	<<"Willkommen, hier kannst du mit dir selbst Kniffel spielen. Die KI folgt bald."<<endl
            <<"Du kannst zwischendurch waehlen, ob du den Spielstand ansehen willst (1/0). Jetzt kanns losgehen!"<<endl<<endl;


    //Abfrage Single- oder Multiplayer
    cout << "Moechtest du im [0]Single- oder [1]Multiplayermodus spielen?" << endl;
    cin >> Spielmodus;


    //KI-MODUS-------------------------------------------------------------------------------------------------------------------------------------------------


        if (Spielmodus == 0)
        {
            Spieler* spielerptr = new Spieler[2];
            double* Erwartungswerte = new double[13];
            int* EintragTemp = new int[13];
            int* order = new int[13];
            int m_temp = 0;
            char Name[15];

              cout << "Bitte gib deinen Namen ein:" << endl;
              cin >> Name;
              spielerptr[0].set_Name(Name);
              spielerptr[0].Spielstand = new int [13]; // FEHLER REPRODUZIEREN: Diese Zeile löschen!
              spielerptr[0].reset_Spielstand();
              //Namen der KI noch beschreiben
              cout <<"Name der KI"<<endl;
              cin >> Name;
              spielerptr[1].set_Name(Name);
              spielerptr[1].Spielstand = new int [13]; // FEHLER REPRODUZIEREN: Diese Zeile löschen!
              spielerptr[1].reset_Spielstand();



              for (int i=0; i<13; i++) // Durchlaufen der 13 Spielzüge
              {
                  for (int l=0; l<2; l++) // Durchlaufen der einzelnen Spieler, hier gibt es nur zwei!
                  {
                      cout << "Nun ist:   " << spielerptr[l].get_Name() << "   an der Reihe" << endl;


                  spielerptr[l].showscore();                      //Spielstandanzeige

                  if (l==0)
                  {
                      for (int j=0; j<5; j++) {keep[j]=0;}            // Beschreibt das Würfelbehaltenfeld mit Nullen
                      for (int j=0; j<3; j++)                         // Nun beginnen die drei Würfe pro Spieler
                      {
                          rolldice(dice, keep);
                          if(j==0||j==1)
                          {
                              cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                              cout <<"behalten? (1/0)	"; for(int k=0; k<5; k++) {cin >>keep[k]; cout<<"   ";}cout<<endl;

                              if(keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
                                  {
                                      write(dice, spielerptr[l].Spielstand);
                                      j=3;										//Für Schleifenabbruch sorgen, da alle Wuerfel behalten werden
                                  }
                              else{}
                          }
                          else
                          {
                              cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                              write(dice, spielerptr[l].Spielstand);
                          }
                      }
                      if (l==1)
                      {
                          for (int j=0; j<5; j++) {keep[j]=0;}            // Beschreibt das Würfelbehaltenfeld mit Nullen
                          for (int j=0; j<3; j++)                         // Nun beginnen die drei Würfe pro Spieler
                          {
                              rolldice(dice, keep);
                              for (int j=0; j<5; j++) {keep[j]=0;}            //??? unsicher: muss das keep feld genau hier hin??
                              //----------------------------------------------------------------------------------------------------------------------------------------------
                              //Erster Wurf der KI

                              if(j==0)
                              {
                                  cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                                  Erwartungswerte[0] = ErwartungswertOben1(dice, 1);
                                  Erwartungswerte[1] = ErwartungswertOben1(dice, 2);
                                  Erwartungswerte[2] = ErwartungswertOben1(dice, 3);
                                  Erwartungswerte[3] = ErwartungswertOben1(dice, 4);
                                  Erwartungswerte[4] = ErwartungswertOben1(dice, 5);
                                  Erwartungswerte[5] = ErwartungswertOben1(dice, 6);
                                  Erwartungswerte[6] = ErwartungswertDreierpasch1(dice);
                                  Erwartungswerte[7] = ErwartungswertViererpasch1(dice);
                                  Erwartungswerte[8] = ErwartungswertFullhouse1(dice);
                                  Erwartungswerte[9] = ErwartungswertklStrasse1(dice);
                                  Erwartungswerte[10]= ErwartungswertgrStrasse1(dice);
                                  Erwartungswerte[11]= ErwartungswertKniffel1(dice);
                                  Erwartungswerte[12]= 0;                                 //Chance

                                  for(int n=0; n<13; n++) cout<<Erwartungswerte[n]<<"   ";
                                  cout<<endl;

                                  sort(Erwartungswerte, order, 13);                   //Erwartungswerte[order[12]] ist der höchste, [0] der kleinste Eintrag

                                  for(int n=0; n<13; n++) cout<<order[n]<<"   ";
                                  cout<<endl;

                                  for (int m=0; m<13; m++)
                                  {
                                      if (spielerptr[1].Spielstand[order[12-m]] == 888)
                                      {
                                          m_temp = m;
                                          setGoal(dice, keep, order[12-m], 0);
                                          cout<<order[12-m]<<endl;
                                          //Ereignis mit dem höchsten Erwartungswert ist noch nicht belegt, es wird als Ziel für den nächsten Wurf gewählt
                                          m = 13;
                                      }
                                  }
                              }

                              //--------------------------------------------------------------------------------------------------------------------------------------------
                              //Zweiter Wurf der KI

                              if(j==1)
                              {
                                  cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                                  Erwartungswerte[0] = ErwartungswertOben2(dice, 1);
                                  Erwartungswerte[1] = ErwartungswertOben2(dice, 2);
                                  Erwartungswerte[2] = ErwartungswertOben2(dice, 3);
                                  Erwartungswerte[3] = ErwartungswertOben2(dice, 4);
                                  Erwartungswerte[4] = ErwartungswertOben2(dice, 5);
                                  Erwartungswerte[5] = ErwartungswertOben2(dice, 6);
                                  Erwartungswerte[6] = ErwartungswertDreierpasch2(dice);
                                  Erwartungswerte[7] = ErwartungswertViererpasch2(dice);
                                  Erwartungswerte[8] = ErwartungswertFullhouse2(dice);
                                  Erwartungswerte[9] = ErwartungswertklStrasse2(dice);
                                  Erwartungswerte[10]= ErwartungswertgrStrasse2(dice);
                                  Erwartungswerte[11]= ErwartungswertKniffel2(dice);
                                  Erwartungswerte[12]= 0;                                 //Chance

                                  for(int n=0; n<13; n++) cout<<Erwartungswerte[n]<<"   ";
                                  cout<<endl;

                                  sort(Erwartungswerte, order, 13);                   //Erwartungswerte[order[12]] ist der höchste, [0] der kleinste Eintrag

                                  for(int n=0; n<13; n++) cout<<order[n]<<"   ";
                                  cout<<endl;

                                  for (int m=0; m<13; m++)
                                  {
                                      if (spielerptr[1].Spielstand[order[12-m]] == 888)
                                      {
                                          m_temp = m;
                                          setGoal(dice, keep, order[12-m], 1);
                                          cout<<order[12-m]<<endl;

                                          //Ereignis mit dem höchsten Erwartungswert ist noch nicht belegt, es wird als Ziel für den nächsten Wurf gewählt
                                          m = 13;
                                      }
                                  }
                              }



                              if((j==0||j==1)&&keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
                              {
                                  write(dice, spielerptr[1].Spielstand, order[12-m_temp]);
                                  j=3;										//Für Schleifenabbruch sorgen, da alle Wuerfel behalten werden
                              }
                              //Nach dem dritten Wurf --------------------------------------------------------------------------------------------------------------------------
                              if(j==2)
                              {
                                  cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                                  for (int p=0; p<13; p++)
                                  {
                                      write(dice, EintragTemp, p+1);
                                      sort(EintragTemp, order, 13);
                                      for (int q=0; q<13; q++)
                                      {
                                          if (spielerptr[1].Spielstand[order[12-p]] == 888)
                                          {
                                              write(dice, spielerptr[1].Spielstand, order[12-p]);
                                              q = 13;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                     }

              delete[] Erwartungswerte;
              Erwartungswerte = NULL;
              delete[] spielerptr;
              spielerptr = NULL;
              delete[] EintragTemp;
              EintragTemp = NULL;
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
                            //write(dice, spielerptr[l].Spielstand); -> das Eintragen passiert jetzt durch Anklicken des Gewinnblatts
                            j=3;										//Für Schleifenabbruch sorgen, wenn vor dem dritten Wurf alle Würfel behalten werden
                        }
				
                }
                else                            //Im dritten Zug wird direkt etwas eingetragen
                {
				cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                //write(dice, spielerptr[l].Spielstand); -> -> das Eintragen passiert jetzt durch Anklicken des Gewinnblatts
                }
            }
           }

    }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Punkteauswertung

    Punkteauswertung(Spieleranzahl,spielerptr);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Bestenliste

    data::bestenliste.fuellenBestenliste(punktzahlBesterSpieler, nameBesterSpieler);        //Überprüfen, ob der Spieler mit den meisten Punkten in die
                                                                                            //Bestenliste mit aufgenommen werden soll


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
