#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include <iostream>
#include <spieler.h>
#endif // FUNKTIONEN_H

using namespace std;

//Variablen (hier als externe definiert, um sie als Prototypen zu kennzeichnen und sie woanders definieren zu können
extern int punktzahlBesterSpieler;
extern char nameBesterSpieler[15];

extern int* dice;						//dice gibt die Würfelergebnisse an
extern int* keep;

//generelle Funktionen
//Funktionsdeklarationen--------------------------------------------------------------------------------------------------------------------------
int countN (int*, int, int);
int sum (int*, int);
int maxindex(int*, int);

//Spielsteuerungsfunktionen
void rolldice (int*, int*);
void showscore (int*);
void write (int*, int*, int);
void Punkteauswertung (int, Spieler*);
void sort (double*, int*, int);
void sort (int*, int*, int);

//Kontrollfunktionen
bool kniffel (int*, int);
bool fullhouse (int*, int);
bool klstrasse (int*, int);
bool grstrasse (int*, int);
bool dreierpasch (int*, int);
bool viererpasch (int*, int);












