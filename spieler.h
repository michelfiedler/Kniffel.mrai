#ifndef SPIELER_H
#define SPIELER_H


#include <iostream>
using namespace std;

//Klassendefinition

class Spieler
{
    public:             //muss public sein, um ihn für die Bestenliste neu zuordnen zu können
        char Name[15];

    public:
        int Punktzahl;
        int* Spielstand;
        int Endpunktzahl;

        void set_Name(char*);
        char* get_Name();
        void showscore();
        void reset_Spielstand();
        int getSpielstand(int);
};


// --------------------------------------------------------------------------------------------------------------------------------


#endif // SPIELER_H
