#ifndef SPIELER_H
#define SPIELER_H


#include <iostream>
#include  <QString>
using namespace std;

//Klassendefinition

class Spieler
{
    public:             //muss public sein, um ihn für die Bestenliste neu zuordnen zu können
        char Name[15];
        enum eSpieleranzahl{
            Zwei,
            Drei,
            Vier,
            Fuenf,
            Sechs,
            Sieben};


    public:
        int Punktzahl;
        int* Spielstand;
        int Endpunktzahl;

        void set_Name(char*);
        char* get_Name();
        void showscore();
        void reset_Spielstand();
        int getSpielstand(int);

        QString mName1;
        QString mName2;
        QString mName3;
        QString mName4;
        QString mName5;
        QString mName6;
        QString mName7;

};


// --------------------------------------------------------------------------------------------------------------------------------


#endif // SPIELER_H
