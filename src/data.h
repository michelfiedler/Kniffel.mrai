#ifndef DATA_H
#define DATA_H

#include "bestenliste.h"
#include "spieler.h"
#include <iostream>
#include <QObject>

class data      //Eine Klasse die Objekte besitzt, die gemeinsam genutzt werden
{
public:
    data();
    ~data();

    static Bestenliste bestenliste; //statisches Objekt der Klasse Bestenliste
    static Spieler singleSpieler;   //statisches Objekt der Klasse Spieler
    static Spieler KI;
    static int Spielmodus;
    static int wievielterWurf;
    static int spieleranzahl;
    static Spieler* spieler;
    static int Zug;
    static int welcherSpieler;
};

#endif // DATA_H
