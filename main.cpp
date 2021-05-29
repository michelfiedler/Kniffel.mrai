#include <iostream>
#include <ctime>
#include <Funktionen.h>

using namespace std;



int main()
{
    srand((unsigned)time(NULL));                //Zufallsfunktion wird mit time initialiesiert

    int spielstand = 0;								//wird als bool verwendet
    int* table = new int[13];					//table speichert die Ergebnisse
    for (int i=0; i<13; i++) table[i] = 888;
    int* dice = new int[5];						//dice gibt die W�rfelergebnisse an
    for (int i=0; i<5; i++) dice[i]=1;
    int* keep = new int[5];					//keep gibt an, welche W�rfel behalten werden sollen
    int Spielmodus;
    int Spieleranzahl;


    cout 	<<"Willkommen, hier kannst du mit dir selbst Kniffel spielen. Die KI folgt bald."<<endl
            <<"Du kannst zwischendurch waehlen, ob du den Spielstand ansehen willst (1/0). Jetzt kanns losgehen!"<<endl<<endl;


    //Abfrage Single- oder Multiplayer
    cout << "Moechtest du im [0]Single- oder [1]Multiplayermodus spielen?" << endl;
    cin >> Spielmodus;

    if (Spielmodus == 0)
    {
        cout << "Die KI kommt bald!" << endl;
    }



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

        //Hier wird gewürfelt
        for (int j=0; j<5; j++) {keep[j]=0;}            //Das keep-Feld wird resetet
		for (int j=0; j<3; j++)
		{
			rolldice(dice, keep);
			if(j==0||j==1)                              //Im ersten und zweiten Zug kann ausgewählt werden, welche Würfel behalten werden
			{
				cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
				cout <<"behalten? (1/0)	"; for(int k=0; k<5; k++) {cin >>keep[k]; cout<<"   ";}cout<<endl;
				
				if(keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1) 
					{
						write(dice, table); 
						j=3;										//Für Schleifenabbruch sorgen
					}
				
			}
			else                            //Im dritten Zug wird direkt etwas eingetragen
			{
				cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
				write(dice, table);
			}
		}

    }

    showscore(table);
        if(sum(table, 7) > 62)
        {
            cout<<"Insgesamt wurden "<<sum(table, 13)+35<<" Punkte erreicht!"<<endl<<endl;
        }
        else
        {
            cout<<"Insgesamt wurden "<<sum(table,13) <<" Punkte erreicht!"<<endl<<endl;
        }



    delete[] table;														//Speicherfreigabe
    table = NULL;
    delete[] dice;
    dice = NULL;
    delete[] keep;
    keep = NULL;

    return 0;

}
