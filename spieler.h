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

        void set_Name(char*);
        char* get_Name();
};

//Methodendefinitionen

void Spieler::set_Name(char* name_neu)
{
    for (int i=0; i<15; i++)
    {
       Name[i]=name_neu[i];
    }
}

char* Spieler::get_Name()
{
    return (this->Name);
}

#endif // SPIELER_H
