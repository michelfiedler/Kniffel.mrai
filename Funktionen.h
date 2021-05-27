#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <iostream>
#endif // FUNKTIONEN_H

int countN (int*, int, int);
int sum (int*, int);
void rolldice (int*, int*);



//----------------------------------------------------------------------------------------------------------------

//Funktionsdefinitionen

int countN (int* zeiger, int laenge, int N) //Zählfunktionen
{
    int anz=0;
    for (int i=0; i<laenge; i++)
    {
        if (zeiger[i]==N) anz++;
    }
    return anz;
}


void rolldice (int* zeiger, int* behalten) //Zufällige Würfelfunktion
{
    for (int k=0; k<5; k++)
    {
        if (behalten[k]==0) {zeiger[k]=(rand()%6)+1;}
    }
}


int sum (int* zeiger, int laenge) //Summenfunktion
{
    int summe=0;
    for (int r=0; r<laenge; r++) summe+=zeiger[r];
    return summe;
}







