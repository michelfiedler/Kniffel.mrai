#ifndef BESTENLISTE_H
#define BESTENLISTE_H

#include "mainwindow.h"

#include <iostream>
#include <QObject>

using namespace std;

class Bestenliste : public QObject //Klasse Bestenliste erstellen, die die Punktzahl und die Namen der Liste enthält und zuordnen kann
{
    Q_OBJECT

public:
    int platz1, platz2, platz3, platz4, platz5;           //Punkte Platz 1 bis 5
    char name1[15], name2[15], name3[15], name4[15], name5[15];     //Namen Platz 1 bis 5

public:
    void fuellenBestenliste(int punktzahl, char* name);
    void set_name(char*, char*);

signals:
   void UpdateBestenliste();
};

#endif // BESTENLISTE_H


