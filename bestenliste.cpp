#include "bestenliste.h"

using namespace std;


void Bestenliste::set_name(char* name_alt, char* name)      //Methode, um die Namen in der Bestenliste neu zuordnen zu können
{
    for (int i=0; i<15; i++)
    {
       name[i]=name_alt[i];
    }
}

void Bestenliste::fuellenBestenliste(int punktzahl, char* name)     //Methode zum Soertieren und Befüllen der Bestenliste
{
    if (punktzahl>platz1)       //Es wird überprüft, ob die zu überprüfende Punktzahl höher als die des Platz 1 der Bestenliste ist
    {
        set_name(name4,name5);  //Es werden jeweils der Name sowie die Punktzahl der Plätze 1 bis 4 einen Platz nach unten verschoben
        set_name(name3,name4);  //und auf Platz 1 der neue Highscore eingefügt
        set_name(name2,name3);
        set_name(name1,name2);
        set_name(name,name1);
        platz5=platz4;
        platz4=platz3;
        platz3=platz2;
        platz2=platz1;
        platz1=punktzahl;
    }
    else if (punktzahl<platz1 && punktzahl>platz2)  //Überprüfen ob die zu überprüfende Punktzahl zwischen Platz 1 und 2 liegt
    {
        set_name(name4,name5);  //Es werden jeweils der Name sowie die Punktzahl der Plätze 2 bis 4 einen Platz nach unten verschoben
        set_name(name3,name4);  //und auf Platz 2 werden der neuen Name sowie die neue Punktzahl eingefügt
        set_name(name2,name3);
        set_name(name,name2);
        platz5=platz4;
        platz4=platz3;
        platz3=platz2;
        platz2=punktzahl;
    }
    else if (punktzahl<platz2 && punktzahl>platz3)  //Überprüfen ob die zu überprüfende Punktzahl zwischen Platz 2 und 3 liegt
    {
        set_name(name4,name5);  //Es werden jeweils der Name sowie die Punktzahl der Plätze 3 bis 4 einen Platz nach unten verschoben
        set_name(name3,name4);  //und auf Platz 3 werden der neuen Name sowie die neue Punktzahl eingefügt
        set_name(name,name3);
        platz5=platz4;
        platz4=platz3;
        platz3=punktzahl;
    }
    else if (punktzahl<platz3 && punktzahl>platz4)  //Überprüfen ob die zu überprüfende Punktzahl zwischen Platz 3 und 4 liegt
    {
        set_name(name4,name5);  //Es werden jeweils der Name sowie die Punktzahl des Platzes 4 nach unten verschoben
        set_name(name,name4);   //und auf Platz 4 werden der neuen Name sowie die neue Punktzahl eingefügt
        platz5=platz4;
        platz4=punktzahl;
    }
    else if (punktzahl<platz4 && punktzahl>platz5)  //Überprüfen ob die zu überprüfende Punktzahl zwischen Platz 4 und 5 liegt
    {
        set_name(name,name5);   //Auf Platz 5 werden der neuen Name sowie die neue Punktzahl eingefügt
        platz5=punktzahl;
    }
    emit UpdateBestenliste();   //Es wird ein Signal gesendet, dass die Bestenliste verändert wurde
}
