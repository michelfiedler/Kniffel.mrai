#ifndef FUNKTIONENKI_H
#define FUNKTIONENKI_H
#include <Funktionen.h>

//Funktionsdeklarationen-------------------------------------------------------------------------------------------------------
double pot (double, int);
int fact (int);
void pick (int*, int*, int, int);
double Bernoulli (int, int, double);
bool EintragLetzterWurf (int*, int*, int*);
void setGoal (int*, int*, int, int);
double ErwartungswertOben1 (int*, int);
double ErwartungswertOben2 (int*, int);
double ErwartungswertDreierPasch1 (int*);
double ErwartungswertDreierPasch2 (int*);
double ErwartungswertViererPasch1 (int*);
double ErwartungswertViererPasch2 (int*);
double ErwartungswertFullhouse1 (int*);
double ErwartungswertFullhouse2 (int*);
double ErwartungswertklStrasse1 (int*);
double ErwartungswertklStrasse2 (int*);
double ErwartungswertgrStrasse1 (int*);
double ErwartungswertgrStrasse2 (int*);
double ErwartungswertKniffel1 (int*);
double ErwartungswertKniffel2 (int*);



#endif // FUNKTIONENKI_H
