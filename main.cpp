#include <iostream>
#include <ctime>
#include <Funktionen.h>
#include <spieler.h>

using namespace std;



int main()
{
    srand((unsigned)time(NULL));                //Zufallsfunktion wird mit time initialiesiert

    int* dice = new int[5];						//dice gibt die Würfelergebnisse an
    for (int i=0; i<5; i++) dice[i]=1;
    int* keep = new int[5];					//keep gibt an, welche Würfel behalten werden sollen
    int Spielmodus;
    int Spieleranzahl;
    int anzeige=0;


    cout 	<<"Willkommen, hier kannst du mit dir selbst Kniffel spielen. Die KI folgt bald."<<endl
            <<"Du kannst zwischendurch waehlen, ob du den Spielstand ansehen willst (1/0). Jetzt kanns losgehen!"<<endl<<endl;


    //Abfrage Single- oder Multiplayer
    cout << "Moechtest du im [0]Single- oder [1]Multiplayermodus spielen?" << endl;
    cin >> Spielmodus;

    if (Spielmodus == 0)
    {
        cout << "Die KI kommt bald!" << endl;
    }

    // ----------------------------------------------------------------------------------------------------------------------------------------------
    // Beginn Multiplayer

        if (Spielmodus == 1)
        {

        //Objektinstanzierung
        do
        {
            cout << "Wie viele Spieler seid ihr?" << endl;
            cin >> Spieleranzahl;
        }
        while(Spieleranzahl<2 || Spieleranzahl>7);


        // Speicheranforderung
        Spieler* spielerptr = new Spieler[Spieleranzahl];


        // Spielerinitialisierung ------------------- Namen eingeben und Spielstände setzen
        char Name[15];
        for (int i=0; i<Spieleranzahl; i++)
        {
            cout << "Bitte gebt eure Namen ein:" << endl;
            cin >> Name;
            spielerptr[i].set_Name(Name);
            spielerptr[i].Spielstand = new int [13];
            spielerptr[i].reset_Spielstand();
        }




    // ----------------------------------------------------------------------------------------------------------------------------------------------
    //Programmablauf

    for (int i=0; i<13; i++) //Durchlauf der 13 Spielzüge
    {
           for (int l=0; l<Spieleranzahl; l++) //Durchlauf der einzelnen Spieler
           {
                cout << "Nun ist:   " << spielerptr[l].get_Name() << "   an der Reihe" << endl;

                                                    //Es wird gefragt, ob der Spielstand angezeigt werden soll und kontrolliert ob die Eingabe korrekt war

            cout <<"Spielstand anzeigen? ";
            cin >> anzeige;
            while (anzeige != 1 && anzeige !=0)
            {
                cout << "Bitte 1 (Spielstand anzeigen) oder 0 (gleich wuerfeln) eingeben." ;
                cin >> anzeige;
            }
            if (anzeige) spielerptr[l].showscore();

            //Hier wird gewürfelt
            for (int j=0; j<5; j++) {keep[j]=0;}            //Das keep-Feld wird resetet
            for (int j=0; j<3; j++)                         //Nun beginnen die drei Würfe pro Spielzug
            {
                rolldice(dice, keep);
                if(j==0||j==1)                              //Im ersten und zweiten Zug kann ausgewählt werden, welche Würfel behalten werden
                {
                    cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                    cout <<"behalten? (1/0)	"; for(int k=0; k<5; k++) {cin >>keep[k]; cout<<"   ";}cout<<endl;
				
                    if(keep[0]==1&&keep[1]==1&&keep[2]==1&&keep[3]==1&&keep[4]==1)
                        {
                            write(dice, spielerptr[l].Spielstand);
                            j=3;										//Für Schleifenabbruch sorgen, wenn vor dem dritten Wurf alle Würfel behalten werden
                        }
				
                }
                else                            //Im dritten Zug wird direkt etwas eingetragen
                {
				cout <<"gewuerfelt:			"; for(int k=0; k<5; k++) {cout <<dice[k]<<"   ";} cout<<endl;
                write(dice, spielerptr[l].Spielstand);
                }
            }
           }

    }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Punkteauswertung

        for (int i=0; i<Spieleranzahl; i++) //Ausgabe des Endspielstandes für jeden Spieler
        {
            cout << spielerptr[i].get_Name() << endl; //Hier noch zu machen: Umwandlung der Spielstandausgabe, sodass alle Spielstände nebeneinander ausgegeben werden
            spielerptr[i].showscore();                //und nicht von jedem Spieler einzeln.

            if(sum(spielerptr[i].Spielstand, 7) > 62)
            {
                cout<<"Insgesamt wurden "<<sum(spielerptr[i].Spielstand, 13)+35<<" Punkte erreicht!"<<endl<<endl;
            }
            else
            {
                cout<<"Insgesamt wurden "<<sum(spielerptr[i].Spielstand,13) <<" Punkte erreicht!"<<endl<<endl;
            }
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Speicherfreigabe
    
    delete[] dice;
    dice = NULL;
    delete[] keep;
    keep = NULL;
    delete[] spielerptr;
    spielerptr = NULL;

    return 0;

}
}
