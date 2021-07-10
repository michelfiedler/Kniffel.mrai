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
double ErwartungswertViererpasch1 (int*, int);
double ErwartungswertViererpasch2 (int*, int);
double ErwartungswertFullhouse1 (int*);
double ErwartunswertFullhouse2 (int*);
double ErwartungswertgrStrasse1 (int*);
double ErwartungswertgrStrasse2 (int*);
double ErwartungswertKniffel1 (int*);
double ErwartunsgwertKniffel2 (int*);

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
    double erwartungswert = anzahl;

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

    //Zählen der jeweils vorliegenden Würfel
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

double ErwartungswertViererpasch1 (int* feld)
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

double ErwartungswertViererpasch2 (int* feld)
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

double ErwartungswertklStrasse2 (int* feld)
{
    double erwartungswert;
    int miss34 = 0;
    int miss25 = 0;
    int miss16 = 0;
    int anzahl[6]={0};
    for (int i=0; i<6; i++)
    {
        anzahl[i]=countN(feld,5,i);
    }

    //Abfrage nach den fehlenden Würfeln unter Beachtung der Wichtigkeit
    if (anzahl[2] == 0) miss34++;
    if (anzahl[3] == 0) miss34++;
    if (anzahl[1] == 0 && anzahl[4] == 0) miss25 = 1;
    if (anzahl[0] == 0 && anzahl[5] == 0) miss16 = 1;

    if (klstrasse(feld,5)) return 30;

    if (miss34==0 && miss25==0 && miss16==0) erwartungswert = 0.556; //34 und 2/5 behalten
    if (miss34==0 && miss25==0 && miss16==1) erwartungswert = 0.556; //34 und 2/5 behalten
    if (miss34==0 && miss25==1 && miss16==0) erwartungswert = 0.361; //nur 3+4 behalten
    if (miss34==0 && miss25==1 && miss16==1) erwartungswert = 0.361; //nur 3+4 behalten
    if (miss34==1 && miss25==0 && miss16==0)
    {
        if ((countN(feld,5,1)>0 && countN(feld,5,2)>0)
         || (countN(feld,5,5)>0 && countN(feld,5,6)>0)
         || (countN(feld,5,2)>0 && countN(feld,5,5)>0)) erwartungswert = 0.361; //1+2, 2+5 oder 5+6 behalten
        else erwartungswert = 0.25; //2/5 behalten
    }
    if (miss34==1 && miss25==0 && miss16==1)
    {
        if (countN(feld,5,2)>0 && countN(feld,5,5)>0) erwartungswert = 0.361; //2+5 wenn möglich
        else erwartungswert = 0.25; //2 oder 5 und 3 behalten
    }
    if (miss34==1 && miss25==1 && miss16==0) erwartungswert = 0.231; //nur 3 behalten
    if (miss34==1 && miss25==1 && miss16==1) erwartungswert = 0.231; //nur 3 behalten
    if (miss34==2 && miss25==0 && miss16==0) erwartungswert = 0.154; //alles neu
    if (miss34==2 && miss25==0 && miss16==1) erwartungswert = 0.154; //alles neu
    if (miss34==2 && miss25==1 && miss16==0) erwartungswert = 0.154; //alles neu
    //Vollständigkeit: Fall "211"  kann es nicht geben

    return erwartungswert*30;
}


//Berechnung des Erwartungswertes für eine große Straße nach dem ersten Wurf
double ErwartungswertgrStrasse1 (int* feld)
{
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
    if (grstrasse(feld,5)) return 40;
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
    if (grstrasse(feld,5)) return 40;
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
