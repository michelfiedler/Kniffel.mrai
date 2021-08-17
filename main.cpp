#include <iostream>
#include <ctime>
#include <QApplication>

#include "mainwindow.h"
#include "Funktionen.h"

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);                 //MainWindow wird initialisiert und geöffnet
    MainWindow w;
    w.show();
    return a.exec();

    srand((unsigned)time(NULL));                //Zufallsfunktion wird mit time initialiesiert
    
    delete[] dice;
    dice = NULL;
    delete[] keep;
    keep = NULL;


    return 0;

}

