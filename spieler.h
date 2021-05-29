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
        void showscore();
        void reset_Spielstand();
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

void Spieler::reset_Spielstand()
{
   for (int i=0; i<13; i++)
   {
     Spielstand[i] = 888;
   }
}

void Spieler::showscore()
{
    cout <<endl<<"SPIELSTAND"<<endl;
    cout <<"1		Einsen			"<<this->Spielstand[0]<<endl;
    cout <<"2		Zweien			"<<this->Spielstand[1]<<endl;
    cout <<"3		Dreien			"<<this->Spielstand[2]<<endl;
    cout <<"4		Vieren			"<<this->Spielstand[3]<<endl;
    cout <<"5		Fuenfen			"<<this->Spielstand[4]<<endl;
    cout <<"6		Sechsen			"<<this->Spielstand[5]<<endl;
    cout <<"7		Dreierpasch		"<<this->Spielstand[6]<<endl;
    cout <<"8		Viererpasch		"<<this->Spielstand[7]<<endl;
    cout <<"9		FullHouse		"<<this->Spielstand[8]<<endl;
    cout <<"10		kl Strasse		"<<this->Spielstand[9]<<endl;
    cout <<"11		gr Strasse		"<<this->Spielstand[10]<<endl;
    cout <<"12		Kniffel			"<<this->Spielstand[11]<<endl;
    cout <<"13		Chance			"<<this->Spielstand[12]<<endl<<endl;
}

// --------------------------------------------------------------------------------------------------------------------------------


#endif // SPIELER_H
