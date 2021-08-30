#include "Funktionen.h"
#include "spieler.h"
#include "data.h"

#include <iostream>

using namespace std;

int* dice = new int[5];
int* keep = new int[5];

//Funktionsdefinitionen

int countN (int* zeiger, int laenge, int N) //Zählfunktionen bekommt einen Zeiger, dessen Länge und den zu zählenden Integer übergeben
{
    int anz=0;
    for (int i=0; i<laenge; i++)    //die Länge des Zeigerfeldes ablaufen und anz erhöhen, wenn Integer vorliegt
    {
        if (zeiger[i]==N) anz++;
    }
    return anz; //gibt die Anzahl des zu zählenden integers zurück
}


void rolldice (int* zeiger, int* behalten)  //Zufällige Würfelfunktion, bekommt ein int-Feld mit Würfeleinträgen und ein int-Feld,
                                            //das Informationen über das Behalten der Würfel enthält, übergeben
{
    for (int k=0; k<5; k++)
    {
        if (behalten[k]==0) {zeiger[k]=(rand()%6)+1;}
    }
}


int sum (int* zeiger, int laenge) //Summenfunktion bekommt einen Zeiger und dessen Länge übergeben
{
    int summe=0;
    for (int r=0; r<laenge; r++) summe+=zeiger[r];  //die Länge des Zeigerfeldes ablaufen und die Einträge addieren
    return summe;   //Summe zurückgeben
}

int maxindex (int* feld, int laenge) //einfache max-Funktion | gibt den Index des Feldeintrages wieder, der den höchsten Wert enthält
{
    int maxindex = 0;
    for (int i=0; i<laenge-1; i++)
    {
        if (feld[maxindex] <= feld[i+1])
        {
            maxindex = i+1;
        }
    }
    return maxindex;
}

void sort(double* feld, int* Reihenfolge, int laenge)   //Bubblesort-Algorithmus, bekommt ein zu sortierendes double-Feld übergeben, welches nicht überschrieben wird
                                                        //Die Reihenfolge der Einträge wird in einem Int-Feld gespeichert, zusätzlich die Länge beider Felder als int
{
    for(int i=0; i<laenge; i++) Reihenfolge[i] = i;

    int temp = 0;
    for(int j = 0; j<laenge-1; j++)
    {
        for(int i=0; i<laenge-1; i++)
        {
            if(feld[Reihenfolge[i]]>feld[Reihenfolge[i+1]])
            {
                temp = Reihenfolge[i];
                Reihenfolge[i] = Reihenfolge[i+1];
                Reihenfolge[i+1] = temp;
            }
        }
    }
}

void sort(int* feld, int* Reihenfolge, int laenge)  //Bubblesort-Algorithmus, bekommt ein zu sortierendes int-Feld übergeben, welches nicht überschrieben wird
                                                    //Die Reihenfolge der Einträge wird in einem Int-Feld gespeichert, zusätzlich die Länge beider Felder als int
{
    for(int i=0; i<laenge; i++) Reihenfolge[i] = i;

    int temp = 0;
    for(int j = 0; j<laenge-1; j++)
    {
        for(int i=0; i<laenge-1; i++)
        {
            if(feld[Reihenfolge[i]]>feld[Reihenfolge[i+1]])
            {
                temp = Reihenfolge[i];
                Reihenfolge[i] = Reihenfolge[i+1];
                Reihenfolge[i+1] = temp;
            }
        }
    }
}

// Kontrollfunktionen
// Alle Kontrollfunktionen bekommen die zu überprüfenden Würfel als int-Feld übergeben und dessen Länge. Sie überprüfen, ob
// ein bestimmtes Ereignis vorliegt und gibt dies als bool zurück

bool kniffel (int* zeiger, int laenge)
{
    for (int i=1; i<7; i++)
    {
        if (countN(zeiger, laenge, i) ==5) return true;
    }
    return false;
}


bool fullhouse (int* zeiger, int laenge)
{
    bool drei = false, zwei = false;
    for (int i=1; i<7; i++)
    {
        if (countN (zeiger, laenge, i) == 2) zwei = true;
        if (countN (zeiger, laenge, i) == 3) drei = true;
    }
    if (zwei == true && drei == true) return true;
    else return false;
}

/*Funktion prüft, ob es sich wirklich um eine kleine Straße handelt. Sie bekommt das Feld mit den Würfeln sowie die Länge
des Feldes übergeben. Handelt es sich um eine kleine Straße wird der bool-Wert true zurück gegeben und sonst false.*/
bool klstrasse (int* zeiger, int laenge)
{
    if (countN(zeiger, laenge, 3)>0&&countN(zeiger, laenge, 4)>0    //Prüfen, ob Würfelwert 3 und 4 vorliegen
        &&((countN(zeiger, laenge, 1)>0&&countN(zeiger, laenge, 2)>0)   //Prüfen, ob zusätzlich Würfelwert 1 und 2 vorliegen oder 2 und 5 oder 5 und 6
        ||(countN(zeiger, laenge, 2)>0&&countN(zeiger, laenge, 5)>0)
        ||(countN(zeiger, laenge, 5)>0&&countN(zeiger, laenge, 6)>0))) return true;
    else return false;
}

/*Funktion prüft, ob es sich wirklich um eine große Straße handelt. Sie bekommt das Feld mit den Würfeln sowie die Länge
des Feldes übergeben. Handelt es sich um eine große Straße wird der bool-Wert true zurück gegeben und sonst false.*/
bool grstrasse (int* zeiger, int laenge)
{
    if (countN(zeiger, laenge, 2)>0&&countN(zeiger, laenge, 3)>0&&countN(zeiger, laenge, 4)>0&&countN(zeiger, laenge, 5)>0  //Prüfen, ob Würfelwerte 2, 3, 4 und 5 vorliegen
       &&((countN(zeiger, laenge, 1)>0||countN(zeiger, laenge, 6)>0))) return true; //Prüfen, ob zusätzlich 1 oder 6 vorliegen
    else return false;
}

//Die boolean Funktion "bool dreierpasch" prüft, ob bei vorhanden Würfeln ein Dreierpasch vorliegt
//Es werden die Würfel als Feld im Parameter zeiger übergeben und die Länge des Würfelfeldes die hier 5 beträgt im Parameter laenge.
bool dreierpasch (int* zeiger, int laenge)
{
    int sum = 0;
    for (int i=1; i<7; i++)                     //für jede mögliche Würfelzahl, wird die For-Schleife einmal durchlaufen
    {
        if (countN(zeiger, laenge, i)>2)        //Es wird überpüft, ob eine Würfelzahl öfter als zwei Mal vorkommt
        {
            for (int j=0; j<laenge; j++)
            {
                sum+=zeiger[j];                 //Addition der gewürfelten Augen der 5 Würfel
            }
            if (sum>0) return true;             //Wenn eine Zahl öfter als zwei Mal auftaucht und die Summe der Würfelaugen größer als 0 ist, wird der Parameter "True" zurückgegeben.
        }
    }
    return false;                               //Taucht keine Zahl öfter als Zwei auf, wird der Parametern false zurückgegeben, es ist kein Dreierpasch.
}

bool viererpasch (int* zeiger, int laenge)
{
    int sum = 0;
    for (int i=1; i<7; i++)
    {
        if (countN(zeiger, laenge, i)>3)
        {
            for (int j=0; j<laenge; j++)
            {
                sum+=zeiger[j];
            }
            if (sum>0) return true;
        }
    }
    return false;
}


void write (int* wuerfel, int* blatt, int was)  //Funktion schreibt die Punkte in den Spielstand rein. Sie bekommt das Feld mit den Würfelwerten und dem Spielstand übergeben
{                                               //Die Variable "was" wird durch das Anklicken des Feldes des Gewinnblatts in der GUI bestimmt

    if(was<7)   //Fall: Es sollen die Punkte für Einsen, Zweien, Dreien, Vieren, Fünfen oder Sechsen in das Spielstandfeld eingetragen werden, indem die Anzahl des Würfelwertes mit ebendiesem multipliziert wird
    {
        blatt[was-1]=was*countN(wuerfel,5,was);
    }
    else
    {
        switch (was)
        {
            case 7: //Fall Dreierpasch: liegt dieser vor wird die Summe der Würfelwerte in das Spielstandfeld eingetragen
            {
                if (dreierpasch(wuerfel,5)) blatt[6]= sum(wuerfel, 5);
                else blatt[6] =0;
                break;
            }
            case 8: //Fall Viererpasch: liegt dieser vor wird die Summe der Würfelwerte in das Spielstandfeld eingetragen
            {
                if(viererpasch(wuerfel,5)) blatt[7] = sum(wuerfel,5);
                else blatt[7]=0;
                break;
            }
            case 9: //Fall Fullhouse: liegt dieses vor wird 25 in das Spielstandfeld eingetragen (selbiges gilt für die Fälle kleine Straße, große Straße und Kniffel entsprechend derer Punkte)
            {
                if(fullhouse(wuerfel,5)) blatt[8] = 25;
                else blatt[8] = 0;
                break;
            }
            case 10:
            {
                if(klstrasse(wuerfel,5)) blatt[9] = 30;
                else blatt[9] =0;
                break;
            }
            case 11:
            {
                if(grstrasse(wuerfel,5)) blatt[10] = 40;
                else blatt[10] = 0;
                break;
            }
            case 12:
            {
                if(kniffel(wuerfel,5)) blatt[11] = 50;
                else blatt[11] =0;
                break;
            }
            case 13:    //Fall Chance: die Summe aller Würfelwerte wird in das Spielstandfeld eingetragen
            {
                blatt[12] = sum(wuerfel,5);
                break;
            }
        }
    }
    data::wievielterWurf=0; //Variable wieder auf 0 setzen, damit für den nächsten Spieler erneut gezählt die Anzahl der Würfe gezählt werden kann
}



