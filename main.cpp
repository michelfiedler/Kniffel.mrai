#include <iostream>
#include <ctime>
#include <Funktionen.h>

using namespace std;



int main()
{
    int spielstand = 0;								//wird als bool verwendet
    int* table = new int[13];					//table speichert die Ergebnisse
    for (int i=0; i<13; i++) table[i] = 888;
    int* dice = new int[5];						//dice gibt die W�rfelergebnisse an
    for (int i=0; i<5; i++) dice[i]=1;
    int* keep = new int[5];					//keep gibt an, welche W�rfel behalten werden sollen



    cout 	<<"Willkommen, hier kannst du mit dir selbst Kniffel spielen. Die KI folgt bald."<<endl
            <<"Du kannst zwischendurch waehlen, ob du den Spielstand ansehen willst (1/0). Jetzt kanns losgehen!"<<endl<<endl;

    for (int i=0; i<13; i++)
    {
                                                        //Es wird gefragt, ob der Spielstand angezeigt werden soll und kontrolliert ob die Eingabe korrekt war
        cout <<"Spielstand anzeigen? ";
        cin >> spielstand;
        while (spielstand != 1 && spielstand !=0)
        {
            cout << "Bitte 1 (Spielstand anzeigen) oder 2 (gleich wuerfeln) eingeben." ;
            cin >> spielstand;
        }
        if (spielstand) showscore(table);




    }




    delete[] table;														//Speicherfreigabe
    table = NULL;
    delete[] dice;
    dice = NULL;
    delete[] keep;
    keep = NULL;

    return 0;

}
