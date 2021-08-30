#include "spieler.h"

#include <iostream>

using namespace std;

//Konstruktordefinition
Spieler::Spieler()
{

}
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

void Spieler::reset_Spielstand()
{
   for (int i=0; i<13; i++)
   {
     Spielstand[i] = 888;
   }
}

int Spieler::getSpielstand(int nummer)
{
    return this->Spielstand[nummer];
}
