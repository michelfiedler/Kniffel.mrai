#ifndef SPIELER_H
#define SPIELER_H


#include <iostream>
using namespace std;

//Klassendefinition

class Spieler
{
    private:
        char Name[15];

    public:
        int Punktzahl;
        int* Spielstand;
};

#endif // SPIELER_H
