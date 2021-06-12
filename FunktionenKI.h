#ifndef FUNKTIONENKI_H
#define FUNKTIONENKI_H

//Funktionsdeklarationen-------------------------------------------------------------------------------------------------------
double pot (double, int);
int fact (int);
double Bernoulli (int, int, double);
double ErwartungswertOben1 (int*, int);

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
        erwartungswert += (Bernoulli(5,matrix[0][i],1.0/6.0)*Bernoulli(5-matrix[0][i],matrix[1][i],1.0/6.0)*(matrix[0][i]+matrix[1][i]));
    }

    return erwartungswert*zahl;
}


#endif // FUNKTIONENKI_H