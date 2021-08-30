#ifndef SPIELER_H
#define SPIELER_H


#include <iostream>
#include  <QString>
using namespace std;

//Klassendefinition

class Spieler
{
    public:
        char Name[15];  //muss public sein, um ihn für die Bestenliste neu zuordnen zu können
        enum eSpieleranzahl{
            Zwei,
            Drei,
            Vier,
            Fuenf,
            Sechs,
            Sieben};


    public:
        Spieler();
        int Punktzahl;
        int* Spielstand;
        int Endpunktzahl;

        void set_Name(char*);
        char* get_Name();
        void showscore();
        void reset_Spielstand();
        int getSpielstand(int);

        QString mName;


};


// --------------------------------------------------------------------------------------------------------------------------------


#endif // SPIELER_H
