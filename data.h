#ifndef DATA_H
#define DATA_H

#include "bestenliste.h"
#include <iostream>
#include <QObject>

class data      //Eine Klasse mit dem statischen Objekt bestenliste aus der Klasse Bestenliste, damit es so gemeinsam genutzt werden kann
{
public:
    data();

    static Bestenliste bestenliste;
};

#endif // DATA_H
