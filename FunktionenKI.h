#ifndef FUNKTIONENKI_H
#define FUNKTIONENKI_H
#include <Funktionen.h>

//Funktionsdeklarationen-------------------------------------------------------------------------------------------------------
double pot (double, int);
int fact (int);
double Bernoulli (int, int, double);
double ErwartungswertOben1 (int*, int);
double ErwartungswertOben2 (int*, int);
double ErwartungswertDreierpasch1 (int*, int);
double ErwartungswertDreierpasch2 (int*, int);
double ErwartungswertgrStrasse1 (int*);
double ErwartungswertKniffel1 (int*);
double ErwartunsgwertKniffel2 (int*);

//Funktionsdefinitionen--------------------------------------------------------------------------------------------------------

//Potenzfunktion mit Basis und Exponent als Übergabeparamter
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Alle folgenden Funktionen geben den Erwartungswert zurück!
/* Die Erwartungswerte sind teilweise per Hand ober über die Simulation eines Baumdiagramms berechnet, bei der die Bedingungen und das Durchlaufen
   der Forschleifen jeweils angepasst wurde.

   Am Ende vieler Funktion wird die berechnete Wahrscheinlichkeit mit der maximal zu erreichenden Punktzahl multipliziert und bildet so den
   Erwartungswert. Ziel ist es dann die verschiedenen Erwartungswerte nach ihrer Größe zu sortieren und das vielversprechendeste Ereignis
   auszuwählen.

   Die folgenden Erwartungswertfunktionen pro Ereignis gliedern sich jeweils in die Funktion nach dem ersten- und zweiten Wurf, sodass die
   Möglichkeit besteht nach dem zweiten Wurf auf ein vielversprechenderes Ereignis zu wechseln.*/


double ErwartungswertOben1 (int* feld, int zahl)
{
    //int** matrix = new int*[2]; //Ziel Matrix dynamisch anfordern!
    //for (int i=0; i<2; i++)
    //{
        //matrix[i] = new int[21];
    //}

    int anzahl = countN(feld, 5, zahl);
    double erwartungswert = anzahl;
    //Matrix zur Möglichkeitendarstellung
    int matrix[2][21] = {{0,0,1,1,0,2,1,2,3,0,0,4,1,3,2,0,5,1,4,3,2},{0,1,0,1,2,0,2,1,0,3,4,0,3,1,2,5,0,4,1,2,3}};
    int obergrenze;

    switch(anzahl)
    {
    case 0: {obergrenze = 21; break;}       //Je nach der bereits existierenden Anzahl ist die Möglichkeitsmatrix
    case 1: {obergrenze = 15; break;}       //unterschiedlich groß
    case 2: {obergrenze = 10; break;}
    case 3: {obergrenze = 6; break;}
    case 4: {obergrenze = 3; break;}
    case 5: {obergrenze = 1; break;}
    }

    for(int i=0; i<obergrenze; i++)
    {
        erwartungswert += (Bernoulli(5-anzahl,matrix[0][i],1.0/6.0)*Bernoulli(5-anzahl-matrix[0][i],matrix[1][i],1.0/6.0)*(matrix[0][i]+matrix[1][i]));
    }

    return erwartungswert*zahl;
}

//Funktion zur Berechnung des Zahlenfeldes nach dem zweiten Wurf, gleiche Übergabeparameter
double ErwartungswertOben2 (int* feld, int zahl)
{
    int anzahl = countN(feld, 5, zahl);
    double erwartungswert = anzahl;

    for(int i=0; i<5-anzahl; i++)
    {
        erwartungswert += (Bernoulli(5-anzahl,i,1.0/6.0))*(i+1);
    }

    return erwartungswert*zahl;
}

double ErwartungswertDreierPasch1 (int* feld)
{
    int* anzahl = new int[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i);
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
        case 5:
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

double ErwartungswertDreierpasch2 (int* feld)
{
    int* anzahl = new int[6];

    for (int i=0; i<6; i++)
    {
       anzahl[i] = countN(feld, 5, i);
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
            if (anzahl[3]%3 == 1 && anzahl[4]%3 == 0 && anzahl[5]%3 == 1) return 12 + 3*mostFrqN;
            break;
        }
    }
}


//Berechnung des Erwartungswertes für eine große Straße nach dem ersten Wurf
double ErwartungswertgrStrasse1 (int* feld)
{
    double erwartungswert;
    int missingones = 0;        //fehlende Würfel, hier 1 und 6
    int keymissingones = 0;     //wichtige fehlende Würfel, hier 2,3,4 und 5, da diese immer benötigt werden
    int anzahl[6]={0};
    for (int i=0; i<6; i++)     //Zählen aller vorliegenden Würfel
    {
        anzahl[i]=countN(feld,5,i+1);
    }

    for (int i=1; i<5; i++)        //Zählen der keymissingones und missingones
    {
       if (anzahl[i]==0) keymissingones++;
    }

    if (anzahl[0]==0 && anzahl[5]==0)missingones++;

    //Fallunterscheidung bezüglich der fehlenden Würfel
    if (grstrasse(feld,5)) return 40;
    if (keymissingones==0) erwartungswert = 5.0/9.0;
    if (keymissingones==1 && missingones==0) erwartungswert = 11.0/36.0;        //Werte alle zuvor ausgerechnet
    if (keymissingones==1 && missingones==1) erwartungswert = 19.0/72.0;
    if (keymissingones==2 && missingones==0) erwartungswert = 121.0/1296.0;
    if (keymissingones==2 && missingones==1) erwartungswert = 307.0/5832.0;
    if (keymissingones==3 && missingones==0) erwartungswert = 2141.0/46656.0;
    if (keymissingones==3 && missingones==1) erwartungswert = 0.01;             //nicht berechnet, da sehr kleine Werte und in diesen Fällen
    if (keymissingones==4 && missingones==0) erwartungswert = 0.005;            // andere Ereignisse vorliegen.


    return erwartungswert*40; //Multiplikation mit der maximal zu erreichenden Punktzahl
}

//Berechnung des Erwartungwertes für einen Kniffel nach dem ersten Wurf
double ErwartungswertKniffel1 (int* feld)
{
    double erwartungswert = 0;
    int anzahl[6];

    for (int i=0; i<6; i++) //Zählen aller vorliegenden Würfel
    {
       anzahl[i] = countN(feld, 5, i+1);
    }

    int maxindex;
    for (int i=0; i<5; i++)     //Bestimmung der Zahl, welche am häufigsten vorliegt
    {
        if (anzahl[i] < anzahl[i+1])
        {
            maxindex = i+1;
        }
    }

    //Fallunterscheidung in Bezug auf die bereits vorliegenden maximale Anzahl
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

    return erwartungswert*50; //Mulitplikation mit der maximal zu erreichenden Punktzahl
}


//Berechnung des Erwartungswertes für einen Kniffel nach dem zweiten Wurf (selbes Vorgehen wie nach dem ersten Wurf)
double ErwartunswertKniffel2 (int* feld)
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

#endif // FUNKTIONENKI_H
