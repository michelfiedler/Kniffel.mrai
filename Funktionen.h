#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <iostream>
#endif // FUNKTIONEN_H

int countN (int*, int, int);
int sum (int*, int);

//Spielsteuerungsfunktionen
void rolldice (int*, int*);

//Kontrollfunktionen
bool kniffel (int*, int);
bool fullhouse (int*, int);
bool klstrasse (int*, int);
bool grstrasse (int*, int);


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


// Kontrollfunktionen

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

bool klstrasse (int* zeiger, int laenge)
{
    if (countN(zeiger, laenge, 3)>0&&countN(zeiger, laenge, 4)>0
        &&((countN(zeiger, laenge, 1)>0&&countN(zeiger, laenge, 2)>0)
        ||(countN(zeiger, laenge, 2)>0&&countN(zeiger, laenge, 5)>0)
        ||(countN(zeiger, laenge, 5)>0&&countN(zeiger, laenge, 6)>0))) return true;
    else return false;
}

bool grstrasse (int* zeiger, int laenge)
{
    if (countN(zeiger, laenge, 2)>0&&countN(zeiger, laenge, 3)>0&&countN(zeiger, laenge, 4)>0&&countN(zeiger, laenge, 5)>0
       &&((countN(zeiger, laenge, 1)>0||countN(zeiger, laenge, 6)>0))) return true;
    else return false;
}
















