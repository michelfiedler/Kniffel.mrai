#ifndef DATA_H
#define DATA_H

#include "bestenliste.h"
#include "spieler.h"
#include <iostream>
#include <QObject>

class data      //Eine Klasse die Objekte besitzt, gemeinsam genutzt werden
{
public:
    data();

    static Bestenliste bestenliste; //statisches Objekt der Klasse Bestenliste
    static Spieler singleSpieler;   //statisches Objekt der Klasse Spieler
    static Spieler KI;
    static int Spielmodus;
    static int wievielterWurf;
};

#endif // DATA_H
