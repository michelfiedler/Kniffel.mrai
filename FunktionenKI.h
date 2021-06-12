#ifndef FUNKTIONENKI_H
#define FUNKTIONENKI_H

//Funktionsdeklarationen-------------------------------------------------------------------------------------------------------
double pot (double, int);
int fact (int);
double Bernoulli (int, int, double);

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




#endif // FUNKTIONENKI_H
