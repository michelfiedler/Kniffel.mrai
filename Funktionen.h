#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <iostream>
#endif // FUNKTIONEN_H

using namespace std;

int countN (int*, int, int);
int sum (int*, int);

//Spielsteuerungsfunktionen
void rolldice (int*, int*);
void showscore (int*);

//Kontrollfunktionen
bool kniffel (int*, int);
bool fullhouse (int*, int);
bool klstrasse (int*, int);
bool grstrasse (int*, int);
bool dreierpasch (int*, int);
bool viererpasch (int*, int);

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

bool dreierpasch (int* zeiger, int laenge)
{
    int sum = 0;
    for (int i=1; i<7; i++)
    {
        if (countN(zeiger, laenge, i)>2)
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

void showscore (int* zeiger)
{
    cout <<endl<<"SPIELSTAND"<<endl;
    cout <<"1		Einsen			"<<zeiger[0]<<endl;
    cout <<"2		Zweien			"<<zeiger[1]<<endl;
    cout <<"3		Dreien			"<<zeiger[2]<<endl;
    cout <<"4		Vieren			"<<zeiger[3]<<endl;
    cout <<"5		Fuenfen			"<<zeiger[4]<<endl;
    cout <<"6		Sechsen			"<<zeiger[5]<<endl;
    cout <<"7		Dreierpasch		"<<zeiger[6]<<endl;
    cout <<"8		Viererpasch		"<<zeiger[7]<<endl;
    cout <<"9		FullHouse		"<<zeiger[8]<<endl;
    cout <<"10		kl Strasse		"<<zeiger[9]<<endl;
    cout <<"11		gr Strasse		"<<zeiger[10]<<endl;
    cout <<"12		Kniffel			"<<zeiger[11]<<endl;
    cout <<"13		Chance			"<<zeiger[12]<<endl<<endl;
}















