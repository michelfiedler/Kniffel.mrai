#include "FunktionenKI.h"

#include <iostream>
#include <cmath>

using namespace std;

//Funktionsdefinitionen-------------------------------------------------------------------------------------------------------------------------------

//Potenzfunktion mit Basis und Exponent als Übergabeparamter und anschließende Berechnung einer beliebigen Potenz
double pot (double basis, int exponent)
{
    double ergebnis = 1;
    for (int i=0; i<exponent; i++)
    {
        ergebnis*=basis;
    }

    return ergebnis;
}

//Fakultätsberechung einer beliebigen Zahl i
int fact(int i)
{
    if (i <= 1) return 1;
    else return i*fact(i-1);
}


//Funktion zur Berechnung der Wahrscheinlichkeit der binomialverteilten Würfel
// mit n=Anzahl durchgeführter Versuche, k=Trefferanzahl, p=Wahrscheinlichkeit
double Bernoulli (int n, int k, double p)
{
    return ((fact(n)/(fact(k)*fact(n-k)))*pot(p,k)*pot(1-p,n-k));
}

//Die Funktion pick wählt aus den Würfeln diejenigen aus die behalten werden (was) und beschreibt das behalten-Feld entsprechend
void pick (int* wuerfel, int* behalten, int was, int anz)
{
    if(countN(wuerfel, 5, was)>0)
    {
        for(int j=0; j<anz; j++)
        {
            for(int i=0; i<5; i++)
            {
                if(wuerfel[i]==was && behalten[i]==0) {behalten[i] = 1; i=5;}
            }
        }
    }
}

bool EintragLetzterWurf (int* Spielstand, int* Reihenfolge, int* wuerfel, int Zug)
{
    for(int i=0; i<13; i++)
    {
        if (Spielstand[Reihenfolge[12-i]] == 888) //Prüfen, ob Feld noch unbeschrieben
        {
            //Wenn kein gutes Ergebnis für 3en, 4en, 5en oder 6en vorliegt, dieses aber eingetragen werden würde
            if(Reihenfolge[12-i]<6 && Reihenfolge[12-i]>1 && countN(wuerfel, 5, Reihenfolge[12-i]+1)<3)
            {
                //-----------------------------------------------------------
                //Streichpriorisierung
                //liegt kein gutes Ergebnis vor, wird vom der KI häufig ein Ereignis eingetragen, welches nicht schlau ist. Die Streichpriorisierung dient als
                //Notlösung und fragt nacheinander mögliche Ereignisse ab, die gestrichen werden können
                //Jeweils wird abgefragt, ob ein Feld schon beschrieben ist. Wenn nicht, wird es beschrieben, die Schleife abgebrochen und true zurückgegeben

                if (Spielstand[12] == 888 && sum(wuerfel, 5)> 15) //Chance eintragen, wenn diese groß genug ist (16 oder mehr)
                {
                    write(wuerfel, Spielstand, 13);
                    return true;
                }
                else if (Spielstand[0] == 888) //Einsen eintragen
                {
                    write(wuerfel, Spielstand, 1);
                    return true;
                }
                else if (Spielstand[11] == 888) //Kniffel streichen
                {
                    write(wuerfel, Spielstand, 12);
                    return true;
                }
                else if (Spielstand[7] == 888) //Viererpasch streichen
                {
                    write(wuerfel, Spielstand, 8);
                    return true;
                }
                else if (Spielstand[1] == 888) //Zweien eintragen
                {
                    write(wuerfel, Spielstand, 2);
                    return true;
                }
                else if (Spielstand[10] == 888) //große Straße streichen
                {
                    write(wuerfel, Spielstand, 11);
                    return true;
                }
                else if (Spielstand[8] == 888) //FullHouse streichen
                {
                    write(wuerfel, Spielstand, 9);
                    return true;
                }

            }
            else if(Reihenfolge[12-i] == 6 && sum(wuerfel, 5)<24)
            {

            }
            else //Eintragen des Ereignisses
            {
                write(wuerfel, Spielstand, Reihenfolge[12-i]+1);
                return true;
            }
        }
    }
    return false;
}

void setGoal (int* wuerfel, int* behalten, int Ereignis, int Wurf)
{
    int* anzahl = new int[6];
    for(int i=0; i<6; i++) anzahl[i] = countN(wuerfel, 5, i+1);

    switch(Ereignis)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    {
        pick(wuerfel, behalten, Ereignis+1, countN(wuerfel, 5, Ereignis+1));
        break;
    }
    case 6:
    {
        int mostFrqN = maxindex(anzahl, 6)+1;
        if(dreierpasch(wuerfel, 5))
        {
            if(Wurf==0)
            {
                pick(wuerfel, behalten, mostFrqN, 3);
                pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
                pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
            }
            if(Wurf==1)
            {
                pick(wuerfel, behalten, mostFrqN, 3);
                pick(wuerfel, behalten, 4, countN(wuerfel, 5, 4));
                pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
                pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
            }
        }
        else
        {
            pick(wuerfel, behalten, mostFrqN, countN(wuerfel, 5, mostFrqN));
        }
        break;
    }
    case 7:
    {
        int mostFrqN = maxindex(anzahl, 6)+1;
        if(viererpasch(wuerfel, 5))
        {
            if(Wurf==0)
            {
                pick(wuerfel, behalten, mostFrqN, 4);
                pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
                pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
            }
            if(Wurf==1)
            {
                pick(wuerfel, behalten, mostFrqN, 4);
                pick(wuerfel, behalten, 4, countN(wuerfel, 5, 4));
                pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
                pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
            }
        }
        else
        {
            pick(wuerfel, behalten, mostFrqN, countN(wuerfel, 5, mostFrqN));
        }
        break;
    }
    case 8:
    {
        int zwilling = 0;
        int drilling = 0;
        if (fullhouse(wuerfel, 5))
        {
            for(int i=0; i<5; i++)
            {
                behalten[i]=1;
            }
            break;
        }

        //Zählen, ob bereits Zwilling (also zwei gleiche Würfel) oder Drillinge (drei gleiche Würfel) vorliegen.
        for (int i = 0; i<6; i++)
        {
            if (countN(wuerfel, 5, i+1)==2) zwilling++;
            if (countN(wuerfel, 5, i+1)>=3) drilling++;

            if (zwilling == 1 && drilling == 0)
            {
                int mostFrqN = maxindex(anzahl, 6)+1;
                pick(wuerfel, behalten, mostFrqN, 2);
            }
            if (zwilling == 0 && drilling == 1)
            {
                int mostFrqN = maxindex(anzahl, 6)+1;
                pick(wuerfel, behalten, mostFrqN, 3);
            }
            if (zwilling == 2 && drilling == 0)
            {
                int ZW1 = 0;
                for (int i=0; i<5; i++)
                {
                    if (anzahl[ZW1] < anzahl[i+1])
                    {
                        ZW1 = i+1;
                    }
                }
                ZW1++;
                int ZW2 = maxindex(anzahl, 6)+1;

                pick(wuerfel, behalten, ZW1, 2);
                pick(wuerfel, behalten, ZW2, 2);
            }
        }
        break;
    }
    case 9:
    {
        if(klstrasse(wuerfel, 5)) //damit er noch die Chance auf die große Straße behält
        {
            pick(wuerfel, behalten, 3, 1);
            pick(wuerfel, behalten, 4, 1);
            if(countN(wuerfel, 5, 2) && countN(wuerfel, 5, 5))
            {
                pick(wuerfel, behalten, 2, 1);
                pick(wuerfel, behalten, 5, 1);
            }
            else if(countN(wuerfel, 5, 2) && countN(wuerfel, 5, 1))
            {
                pick(wuerfel, behalten, 2, 1);
                pick(wuerfel, behalten, 1, 1);
            }
            else if(countN(wuerfel, 5, 5) && countN(wuerfel, 5, 6))
            {
                pick(wuerfel, behalten, 5, 1);
                pick(wuerfel, behalten, 6, 1);
            }
         }
        else
        {
            pick(wuerfel, behalten, 3, 1);
            pick(wuerfel, behalten, 4, 1);

            int miss34 = 0;
            int miss25 = 0;
            int miss16 = 0;

            if (anzahl[2] == 0) miss34++;
            if (anzahl[3] == 0) miss34++;
            if (anzahl[1] == 0 && anzahl[4] == 0) miss25 = 1;
            if (anzahl[0] == 0 && anzahl[5] == 0) miss16 = 1;

            if (miss34==1 && miss25==0 && miss16==0) //1+2, 2+5 oder 5+6 behalten, wenn das nicht geht: 2/5 behalten
            {
                if (countN(wuerfel,5,1)>0 && countN(wuerfel,5,2)>0) {pick(wuerfel, behalten, 1, 1); pick(wuerfel, behalten, 2, 1);}
                else if (countN(wuerfel,5,5)>0 && countN(wuerfel,5,6)>0) {pick(wuerfel, behalten, 5, 1); pick(wuerfel, behalten, 6, 1);}
                else if (countN(wuerfel,5,2)>0 && countN(wuerfel,5,5)>0) {pick(wuerfel, behalten, 2, 1); pick(wuerfel, behalten, 5, 1);}
                else {pick(wuerfel, behalten, 2, 1); pick(wuerfel, behalten, 5, 1);}
            }
            else {pick(wuerfel, behalten, 2, 1); pick(wuerfel, behalten, 5, 1);}
        }
        break;
    }
    case 10:
    {
        if(grstrasse(wuerfel, 5)) for(int i=0; i<5; i++) behalten[i]=1;

        pick(wuerfel, behalten, 2, 1);
        pick(wuerfel, behalten, 3, 1);
        pick(wuerfel, behalten, 4, 1);
        pick(wuerfel, behalten, 5, 1);

        if (countN(wuerfel, 5, 1)>0 && countN(wuerfel, 5, 2)>0 && countN(wuerfel, 5, 3)>0 && countN(wuerfel, 5, 4)>0) pick(wuerfel, behalten, 1, 1);
        if (countN(wuerfel, 5, 3)>0 && countN(wuerfel, 5, 4)>0 && countN(wuerfel, 5, 5)>0 && countN(wuerfel, 5, 6)>0) pick(wuerfel, behalten, 6, 1);
        break;
    }
    case 11:
    {
        int mostFrqN = maxindex(wuerfel, 5)+1;
        pick(wuerfel, behalten, mostFrqN, countN(wuerfel, 5, mostFrqN));
        break;
    }
    case 12:
    {
        if(Wurf==0)
        {
            pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
            pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
        }
        if(Wurf==1)
        {
            pick(wuerfel, behalten, 4, countN(wuerfel, 5, 4));
            pick(wuerfel, behalten, 5, countN(wuerfel, 5, 5));
            pick(wuerfel, behalten, 6, countN(wuerfel, 5, 6));
        }
        break;
    }
    }
    delete[] anzahl;
    anzahl = NULL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Alle folgenden Funktionen geben den Erwartungswert zurück!
/* Die Erwartungswerte sind teilweise per Hand ober über die Simulation eines Baumdiagramms berechnet, bei der die Bedingungen und das Durchlaufen
   der Forschleifen jeweils angepasst wurde.

   Am Ende vieler Funktion wird die berechnete Wahrscheinlichkeit mit der maximal zu erreichenden Punktzahl multipliziert und bildet so den
   Erwartungswert. Ziel ist es dann die verschiedenen Erwartungswerte nach ihrer Größe zu sortieren und das vielversprechendeste Ereignis
   auszuwählen.

   Die folgenden Erwartungswertfunktionen pro Ereignis gliedern sich jeweils in die Funktion nach dem ersten- und zweiten Wurf, sodass die
   Möglichkeit besteht nach dem zweiten Wurf auf ein vielversprechenderes Ereignis zu wechseln. Allen Erwartungswertfunktionen wird das Würfelfeld
   übergeben und für die Erwartungswerte des oberen Zahlenblockes wird den Funktionen ebenfalls die jeweilge Zahl übergeben. */


double ErwartungswertOben1 (int* feld, int zahl)
{
    //Zählen, wie oft die übergebene Zahl im Würfelfeld vorliegt
    int anzahl = countN(feld, 5, zahl);
    double erwartungswert = pow(anzahl, 2.3); //Anzahl wird aufgrund des Kniffelbonus höher gewichtet

  /*Die folgende Matrix wird mit allen möglichen Würfelkombinationen beschrieben, welche ich mit zwei Würfen erzielen kann.
    Bezogen wird dies immer auf eine bestimmte Zahl:
    Das bedeutet bspw, dass weder im ersten, noch im zweiten Wurf die gewünschte Zahl erzielt wurde (entspreche dann dem Fall (0/0)
    in er Matrix oder ich erreiche im ersten Wurf 4-mal meine gewünschte Zahl und im zweiten Wurf dann entweder keinmal oder
    einmal, denn diese beiden Möglichkeiten bleiben bei insgesamt fünf Würfeln noch übrig.

    Im folgenden wird dann zwischen der Obergrenze unterschieden, abhängig davon, wie viele Würfel meiner gewünschten Zahl ich im
    ersten Wurf schon erreicht habe, ändert sich die Anzahl der noch möglichen Würfelkombinationen. Wenn ich schon zwei Würfel der gewünschten
    Zahl im ersten Wurf habe, kann ich in den folgenden zweien nur noch maximal 3 Würfel meiner gewünschten Zahl dazu erreichen.*/

    int matrix[2][21] = {{0,0,1,1,0,2,1,2,3,0,0,4,1,3,2,0,5,1,4,3,2},{0,1,0,1,2,0,2,1,0,3,4,0,3,1,2,5,0,4,1,2,3}};
    int obergrenze;

    switch(anzahl)
    {
    case 0: {obergrenze = 21; break;}
    case 1: {obergrenze = 15; break;}
    case 2: {obergrenze = 10; break;}
    case 3: {obergrenze = 6; break;}
    case 4: {obergrenze = 3; break;}
    case 5: {obergrenze = 1; break;}
    }

    //Abhängig von der Obergrenze wird nun die jeweilige Wahrscheinlichkeit ausgerechnet
    for(int i=0; i<obergrenze; i++)
    {
        erwartungswert += (Bernoulli(5-anzahl,matrix[0][i],1.0/6.0)*Bernoulli(5-anzahl-matrix[0][i],matrix[1][i],1.0/6.0)*(matrix[0][i]+matrix[1][i]));
    }

    return erwartungswert*zahl;
}

//Funktion zur Berechnung des Zahlenfeldes nach dem zweiten Wurf
double ErwartungswertOben2 (int* feld, int zahl)
{
    int anzahl = countN(feld, 5, zahl);
    double erwartungswert = pow(anzahl, 1.7); //Anzahl wird aufgrund des Kniffelbonus höher gewichtet

    for(int i=0; i<5-anzahl; i++)
    {
        erwartungswert += (Bernoulli(5-anzahl,i,1.0/6.0))*(i+1);
    }

    return erwartungswert*zahl;
}

double ErwartungswertDreierPasch1 (int* feld)
{
    int* anzahl = new int[6];

    //Zählen der jeweils vorliegenden Würfel
    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int mostFrqN = maxindex(anzahl,6)+1;

    //Fallunterscheidung in Bezug auf die bereits vorliegende Anzahl
    switch (anzahl[mostFrqN-1])
    {
        case 1: //Man würde alle nochmal würfeln, dann dann die Wahrscheinlichkeit höher ist (WICHTIG: ABLAUFSTEUERUNG)
        {
            return 10.0857;
            break;
        }
        case 2:
        {
            return 0.02036*mostFrqN*mostFrqN + 1.967*mostFrqN + 6.1251;
            break;
        }
        case 3: //Ab diesem Case ist der Dreierpasch bereits erreicht
        {

        }
        case 4:
        {

        }
        case 5:/*Hier erfolgt die Fallunterscheidung bezüglich der Würfel, welche nicht Teil des Dreierpasches sind. Da beim Dreierpasch
             jedoch die Summe miteinbezogen wird, muss man den Erwartunsgwert weiter auffächern. Die KI soll weiter würfeln, auch wenn der
             Dreierpasch schon erreicht ist, um die maximal zu erreichende Punktzahl zu steigern

             Der durchschnittliche Erwartungswert für jeden Würfel bei noch zwei Würfen beträgt 4.25, weshalb hier nur nach den 5 und 6
             unterschieden wird, da die 4 noch mal gewürfelt werden würde. */
        {
            if (anzahl[4]%3 == 0 && anzahl[5]%3 == 0) return 8.5 + 3*mostFrqN;
            if (anzahl[4]%3 == 1 && anzahl[5]%3 == 0) return 9.25 + 3*mostFrqN;
            if (anzahl[4]%3 == 2 && anzahl[5]%3 == 0) return 10 + 3*mostFrqN;
            if (anzahl[4]%3 == 0 && anzahl[5]%3 == 1) return 10.25 + 3*mostFrqN;
            if (anzahl[4]%3 == 1 && anzahl[5]%3 == 1) return 11 + 3*mostFrqN;
            if (anzahl[4]%3 == 0 && anzahl[5]%3 == 2) return 12 + 3*mostFrqN;
            break;
        }
    }
}

double ErwartungswertDreierPasch2 (int* feld)
{
    int* anzahl = new int[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int mostFrqN = maxindex(anzahl,6)+1;

    switch (anzahl[mostFrqN-1])
    {
        case 1: //Man würde alle nochmal würfeln, da dann die Wahrscheinlichkeit höher ist
        {
            return 0.212963*17.5;
            break;
        }
        case 2:
        {
            return (Bernoulli(3,1,1.0/6.0)+Bernoulli(3,2,1.0/6.0)+Bernoulli(3,3,1.0/6.0))*(3*mostFrqN+7);
            break;
        }
        case 3:
        {

        }
        case 4:
        {

        }
        case 5:     /* Erneute Fallunterscheidung der übrigen Würfel, hier wird im Gegensatz zu oben bereist ab der 4
                       unterschieden, da der Erwartungswert für zwei Würfel bei noch einem Wurf nun bei 3.5 liegt */
        {
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 0 && anzahl[5]%3 == 0) return 7 + 3*mostFrqN;
            if (anzahl[3]%3 == 1 && anzahl[4]%3 == 0 && anzahl[5]%3 == 0) return 7.5 + 3*mostFrqN;
            if (anzahl[3]%3 == 2 && anzahl[4]%3 == 0 && anzahl[5]%3 == 0) return 8 + 3*mostFrqN;
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 1 && anzahl[5]%3 == 0) return 8.5 + 3*mostFrqN;
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 2 && anzahl[5]%3 == 0) return 10 + 3*mostFrqN;
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 0 && anzahl[5]%3 == 1) return 9.5 + 3*mostFrqN;
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 0 && anzahl[5]%3 == 2) return 12 + 3*mostFrqN;
            if (anzahl[3]%3 == 1 && anzahl[4]%3 == 1 && anzahl[5]%3 == 0) return 9 + 3*mostFrqN;
            if (anzahl[3]%3 == 0 && anzahl[4]%3 == 1 && anzahl[5]%3 == 1) return 11 + 3*mostFrqN;
            if (anzahl[3]%3 == 1 && anzahl[4]%3 == 0 && anzahl[5]%3 == 1) return 10 + 3*mostFrqN;
            else return 0;
            break;
        }
    }
}

double ErwartungswertViererPasch1 (int* feld)
{
    int* anzahl = new int[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int mostFrqN = maxindex(anzahl, 6)+1;

    switch (anzahl[mostFrqN-1])
    {
    case 1: //Man würde alle nochmal würfeln
    {
        return 2.379;
        break;
    }
    case 2:
    {
        return 0.975 + 0.889*mostFrqN - 0.00328*mostFrqN*mostFrqN;
        break;
    }
    case 3:
    {
        return 2.073*mostFrqN + 2.043;
    }
    case 4:     //Ab diesem Case ist der Viererpasch bereits erreicht
    {

    }
    case 5:
    {
        if (anzahl[4]%4 == 0 && anzahl[5]%4 == 0) return 4.25 +4*mostFrqN;
        if (anzahl[4]%4 == 1 && anzahl[5]%4 == 0) return 5 + 4*mostFrqN;
        if (anzahl[4]%4 == 0 && anzahl[5]%4 == 1) return 6 + 4*mostFrqN;
        break;
    }
    }
}

double ErwartungswertViererPasch2 (int* feld)
{
    int* anzahl = new int[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int mostFrqN = maxindex(anzahl, 6)+1;

    switch (anzahl[mostFrqN-1])
    {
    case 1: //Man würde alle nochmal würfeln, da dann die Wahrscheinlichkeit höher ist
    {
        return 0.0200617*17.5;
        break;
    }
    case 2:
    {
        return (Bernoulli(3,2,1.0/6.0)+Bernoulli(3,3,1.0/6.0))*(4*mostFrqN+3.5);
        break;
    }
    case 3:
    {
        return (Bernoulli(2,1,1.0/6.0)+Bernoulli(2,2,1.0/6.0))*(4*mostFrqN+3.5);
        break;
    }
    case 4:
    {

    }
    case 5:
    {
        if (anzahl[3]%4 == 0 && anzahl[4]%4 == 0 && anzahl[5]%4 == 0) return 3.5 + 4*mostFrqN;
        if (anzahl[3]%4 == 1 && anzahl[4]%4 == 0 && anzahl[5]%4 == 0) return 4 + 4*mostFrqN;
        if (anzahl[3]%4 == 0 && anzahl[4]%4 == 1 && anzahl[5]%4 == 0) return 5 + 4*mostFrqN;
        if (anzahl[3]%4 == 0 && anzahl[4]%4 == 0 && anzahl[5]%4 == 1) return 6 + 4*mostFrqN;
        break;
    }

    }
}

//Funktion zur Berechnung des Erwartungswertes für ein Fullhouse nach dem ersten Wurf
double ErwartungswertFullhouse1 (int* feld)
{
    //Prüfung, ob bereits ein Fullhouse vorliegt
    if (fullhouse(feld,5)) return 25;

    double erwartungswert;
    int anzahl[6];

    //Zählen aller vorliegenden Würfel und speichern dieser im Anzahl-Feld
    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int zwilling = 0;
    int drilling = 0;

    //Zählen, ob bereits Zwillinge (also zwei gleiche Würfel) oder ein Drilling (drei gleiche Würfel) vorliegen.
    for (int i = 0; i<6; i++)
    {
        if (anzahl[i]==2) zwilling++;
        if (anzahl[i]>=3) drilling++;
    }

    //Fallunterscheidung hinsichtlich der Anzahl vorliegender Zwillinge und Drillinge
    //Berechnung der jeweiligen Erwartungswerte mit dem Simulationsprogramm
    if (zwilling == 0 && drilling == 0) erwartungswert = 0.179;

    if (zwilling == 1 && drilling == 0) erwartungswert = 0.204;

    if (zwilling == 0 && drilling == 1) erwartungswert = 0.259;

    if (zwilling == 2 && drilling == 0) erwartungswert = 5.0/9.0;


    return erwartungswert*25; //Multilplikation mit der maximal zu erreichenden Punktzahl und Rückgabe des Erwartungswertes
}

double ErwartungswertFullhouse2 (int* feld) //Selbes Vorgehen wie oben, nur nach dem zweiten Wurf
{
    if (fullhouse(feld,5)) return 25;

    double erwartungswert;
    int anzahl[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int zwilling = 0;
    int drilling = 0;

    for (int i = 0; i<6; i++)
    {
        if (anzahl[i]==2) zwilling++;
        if (anzahl[i]>=3) drilling++;
    }

    if (zwilling == 0 && drilling == 0) erwartungswert = 0.0385;

    if (zwilling == 1 && drilling == 0) erwartungswert = 0.02314;

    if (zwilling == 0 && drilling == 1) erwartungswert = 5.0/36.0;

    if (zwilling == 2 && drilling == 0) erwartungswert = 1.0/3.0;


    return erwartungswert*25;

}

double ErwartungswertklStrasse1 (int* feld)
{
    if (klstrasse(feld,5)) return 30;           //Falls kleine Straße schon vorhanden: Erwartungswert ist 30

    //Die folgenden Variablen dienen der späteren Fallunterscheidung. Sie beschreiben, ob die entsprechenden Zahlen im Würfelfeld NICHT vorhanden sind
    int miss34 = 0;             //Zählt fehlende 3en und 4en
    int miss25 = 0;             //Zählt fehlende 2en und 5en
    int miss16 = 0;             //Zählt fehlende 1en und 6en

    //Abfrage nach den fehlenden Würfeln
    if (countN(feld,5,3) == 0) miss34++;        //weder 3 noch 4 vorhanden: 2, entweder 3 oder 4 vorhanden: 1, beide vorhanden: 0
    if (countN(feld,5,4) == 0) miss34++;
    if (countN(feld,5,2) == 0 && countN(feld,5,5) == 0) miss25 = 1;     //weder 2 noch 5 vorhanden: 1, entweder 2 oder 5 vorhanden oder beide: 0
    if (countN(feld,5,1) == 0 && countN(feld,5,6) == 0) miss16 = 1;     //weder 1 noch 6 vorhanden: 1, entweder 1 oder 6 vorhanden oder beide: 0

    //Die zu den Erwartungswerten zugehörigen Wahrscheinlichkeiten wurden teilweise mittels Simulation bestimmt, teils berechnet
    if (miss34==0 && miss25==0 && miss16==0) return 30*65.0/81.0;
    if (miss34==0 && miss25==0 && miss16==1) return 30*65.0/81.0;
    if (miss34==0 && miss25==1 && miss16==0) return 30*0.658; //nur 3+4 behalten
    if (miss34==0 && miss25==1 && miss16==1) return 30*0.658;
    if (miss34==1 && miss25==0 && miss16==0) //1+2, 2+5 oder 5+6 behalten (0.518), wenn das nicht geht: 2/5 behalten (0.490)
    {
        if ((countN(feld,5,1)>0 && countN(feld,5,2)>0)
         || (countN(feld,5,5)>0 && countN(feld,5,6)>0)
         || (countN(feld,5,2)>0 && countN(feld,5,5)>0)) return 30*0.518;
        else return 30*0.49;
    }
    if (miss34==1 && miss25==0 && miss16==1) //2+5 wenn möglich (0.518), sonst: 2 oder 5 und 3 behalten (0.424)
    {
        if (countN(feld,5,2)>0 && countN(feld,5,5)>0) return 30*0.518;
        else return 30*0.424;
    }
    if (miss34==1 && miss25==1 && miss16==0) return 30*0.426;
    if (miss34==1 && miss25==1 && miss16==1) return 30*0.588;
    if (miss34==2 && miss25==0 && miss16==0) return 30*0.389; //alles neu (im 2.Wurf 3+4 behalten, 2/5 behalten)
    if (miss34==2 && miss25==0 && miss16==1) return 30*0.389; //alles neu (im 2.Wurf 3+4 behalten, 2/5 behalten)
    if (miss34==2 && miss25==1 && miss16==0) return 30*0.389; //alles neu (im 2.Wurf 3+4 behalten, 2/5 behalten)
    //Vollständigkeit: Fall "211"  kann es nicht geben
    else return 0;          //Theoretisch sind alle 11 bzw. 12 Fälle abgedeckt, da die Steuervariablen keine anderen Fälle annehmen können
                            //Zur Problemvorbeugung soll 0 zurückgegeben werden
}

double ErwartungswertklStrasse2 (int* feld)
{
   //Die folgenden Variablen dienen der späteren Fallunterscheidung. Sie beschreiben, ob die entsprechenden Zahlen im Würfelfeld NICHT vorhanden sind
    int miss34 = 0;             //Zählt fehlende 3en und 4en
    int miss25 = 0;             //Zählt fehlende 2en und 5en
    int miss16 = 0;             //Zählt fehlende 1en und 6en

    //Abfrage nach den fehlenden Würfeln
    if (countN(feld,5,3) == 0) miss34++;        //weder 3 noch 4 vorhanden: 2, entweder 3 oder 4 vorhanden: 1, beide vorhanden: 0
    if (countN(feld,5,4) == 0) miss34++;
    if (countN(feld,5,2) == 0 && countN(feld,5,5) == 0) miss25 = 1;     //weder 2 noch 5 vorhanden: 1, entweder 2 oder 5 vorhanden oder beide: 0
    if (countN(feld,5,1) == 0 && countN(feld,5,6) == 0) miss16 = 1;     //weder 1 noch 6 vorhanden: 1, entweder 1 oder 6 vorhanden oder beide: 0

    if (klstrasse(feld,5)) return 30;

    if (miss34==0 && miss25==0 && miss16==0) return 30*0.556; //34 und 2/5 behalten
    if (miss34==0 && miss25==0 && miss16==1) return 30*0.556; //34 und 2/5 behalten
    if (miss34==0 && miss25==1 && miss16==0) return 30*0.361; //nur 3+4 behalten
    if (miss34==0 && miss25==1 && miss16==1) return 30*0.361; //nur 3+4 behalten
    if (miss34==1 && miss25==0 && miss16==0)
    {
        if ((countN(feld,5,1)>0 && countN(feld,5,2)>0)
         || (countN(feld,5,5)>0 && countN(feld,5,6)>0)
         || (countN(feld,5,2)>0 && countN(feld,5,5)>0)) return 30*0.361; //1+2, 2+5 oder 5+6 behalten
        else return 30*0.25; //2/5 behalten
    }
    if (miss34==1 && miss25==0 && miss16==1)
    {
        if (countN(feld,5,2)>0 && countN(feld,5,5)>0) return 30*0.361; //2+5 wenn möglich
        else return 30*0.25; //2 oder 5 und 3 behalten
    }
    if (miss34==1 && miss25==1 && miss16==0) return 30*0.231; //nur 3 behalten
    if (miss34==1 && miss25==1 && miss16==1) return 30*0.231; //nur 3 behalten
    if (miss34==2 && miss25==0 && miss16==0) return 30*0.154; //alles neu
    if (miss34==2 && miss25==0 && miss16==1) return 30*0.154; //alles neu
    if (miss34==2 && miss25==1 && miss16==0) return 30*0.154; //alles neu
    //Vollständigkeit: Fall "211"  kann es nicht geben
    else return 0;          //Theoretisch sind alle 11 bzw. 12 Fälle abgedeckt, da die Steuervariablen keine anderen Fälle annehmen können
                            //Zur Problemvorbeugung soll 0 zurückgegeben werden
}


//Berechnung des Erwartungswertes für eine große Straße nach dem ersten Wurf
double ErwartungswertgrStrasse1 (int* feld)
{
    if (grstrasse(feld,5)) return 40;

    double erwartungswert;
    int missingones = 0;        //entspricht den fehlenden Würfeln, hier 1 und 6
    int keymissingones = 0;     //entspricht den wichtigen fehlende Würfeln, hier 2,3,4 und 5, da diese immer für eine große Straße benötigt werden
    int anzahl[6]={0};

    //Zählen aller vorliegenden Würfel
    for (int i=0; i<6; i++)
    {
        anzahl[i]=countN(feld,5,i+1);
    }

    //Zählen der keymissingones und missingones
    for (int i=1; i<5; i++)
    {
       if (anzahl[i]==0) keymissingones++;
    }

    if (anzahl[0]==0 && anzahl[5]==0)missingones++;

    //Fallunterscheidung bezüglich der fehlenden Würfel
    //Berechnung der Werte mit dem Simulationsprogramm
    if (keymissingones==0) erwartungswert = 5.0/9.0;
    if (keymissingones==1 && missingones==0) erwartungswert = 11.0/36.0;
    if (keymissingones==1 && missingones==1) erwartungswert = 19.0/72.0;
    if (keymissingones==2 && missingones==0) erwartungswert = 121.0/1296.0;
    if (keymissingones==2 && missingones==1) erwartungswert = 307.0/5832.0;
    if (keymissingones==3 && missingones==0) erwartungswert = 2141.0/46656.0;
    if (keymissingones==3 && missingones==1) erwartungswert = 0.01;             //nicht berechnet, da sehr kleine Werte und in diesen Fällen
    if (keymissingones==4 && missingones==0) erwartungswert = 0.005;            // andere Ereignisse vorliegen.


    return erwartungswert*40; //Multiplikation mit der maximal zu erreichenden Punktzahl und Rückgabe des Erwartungswertes
}

//Berechnung des Erwartungswertes nach dem zweiten Wurf (selbes Vorgehen wie nach dem ersten Wurf)
double ErwartungswertgrStrasse2 (int* feld)
{
    if (grstrasse(feld,5)) return 40;

    double erwartungswert;
    int missingones = 0;
    int keymissingones = 0;
    int anzahl[6]={0};
    for (int i=0; i<6; i++)
    {
        anzahl[i]=countN(feld,5,i+1);
    }

    for (int i=1; i<5; i++)
    {
       if (anzahl[i]==0) keymissingones++;
    }

    if (anzahl[0]==0||anzahl[5]==0)missingones++;

    //Fallunterscheidung
    if (keymissingones==0) erwartungswert = 1.0/3.0;
    if (keymissingones==1 && missingones==0) erwartungswert = 1.0/6.0;
    if (keymissingones==1 && missingones==1) erwartungswert = 1.0/9.0;
    if (keymissingones==2 && missingones==0) erwartungswert = 1.0/18.0;
    if (keymissingones==2 && missingones==1) erwartungswert = 1.0/18.0;
    if (keymissingones==3 && missingones==0) erwartungswert = 1.0/36.0;
    if (keymissingones==3 && missingones==1) erwartungswert = 4.0/109.0;
    if (keymissingones==4 && missingones==0) erwartungswert = 1.0/312.0;


    return erwartungswert*40;
}

//Berechnung des Erwartungwertes für einen Kniffel nach dem ersten Wurf
double ErwartungswertKniffel1 (int* feld)
{
    double erwartungswert = 0;
    int anzahl[6];

    //Zählen aller vorliegenden Würfel
    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    //Bestimmung der Zahl, welche am häufigsten vorliegt mithilfe eines Max-Algorithmus
    int maxindex;
    for (int i=0; i<5; i++)
    {
        if (anzahl[i] < anzahl[i+1])
        {
            maxindex = i+1;
        }
    }

    //Fallunterscheidung in Bezug auf die bereits vorliegende maximale Anzahl
    //Berechnung der jeweiligen Erwartunsgwerte
    switch (anzahl[maxindex])
    {
    case 1:
    {
        erwartungswert = 0.012025;
        break;
    }

    case 2:
    {
        erwartungswert = 0.02906325;
        break;
    }
    case 3:
    {
        erwartungswert = 91.0/1296.0;
        break;
    }
    case 4:
    {
        erwartungswert = 11.0/36.0;
        break;
    }
    case 5:
    {
        erwartungswert = 1;
        break;
    }

    }

    return erwartungswert*50; //Mulitplikation mit der maximal zu erreichenden Punktzahl und Rückgabe des Erwartungswertes
}


//Berechnung des Erwartungswertes für einen Kniffel nach dem zweiten Wurf (selbes Vorgehen wie nach dem ersten Wurf)
double ErwartungswertKniffel2 (int* feld)
{
    double erwartungswert;
    int anzahl[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int maxindex;
    for (int i=0; i<5; i++)
    {
        if (anzahl[i] < anzahl[i+1])
        {
            maxindex = i+1;
        }
    }

    switch (anzahl[maxindex])
    {
    case 1:
    {
        erwartungswert = 1.0/1296.0;
        break;
    }

    case 2:
    {
        erwartungswert = 1.0/216.0;
        break;
    }
    case 3:
    {
        erwartungswert = 1.0/36.0;
        break;
    }
    case 4:
    {
        erwartungswert = 1.0/6.0;
        break;
    }
    case 5:
    {
        erwartungswert = 1;
        break;
    }

    }


    return erwartungswert*50;
}
