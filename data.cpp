#include "data.h"

data::data()
{

}

data::~data()
{
    delete [] spieler;
    spieler = NULL;
}

Bestenliste data::bestenliste;      //Objekt bestenliste erstellen vom Typ Bestenliste
Spieler data::singleSpieler;        //Objekt singleSpieler erstellen vom Typ Spieler
Spieler data::KI;
int data::Spielmodus=0;
int data::wievielterWurf=0;
int data::spieleranzahl=0;
int data::Zug=0;
int data::welcherSpieler=0;
Spieler* data::spieler = new Spieler[7]; //Speicheranforderung für Spieler

