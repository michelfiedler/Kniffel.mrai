#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bestenliste.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->setupUi(this);

       ifstream bestenlisteLesenFile3;
       bestenlisteLesenFile3.open("Bestenliste.conf");
       string lines;
       while(getline(bestenlisteLesenFile3, lines))
           ui->label->setText();


       bestenlisteLesenFile3.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBeenden_triggered()    //Das Programm "Kniffel" wird geschlossen
{
    this->close();
}


void MainWindow::on_pBsingle_clicked()          //Button Singleplayer wurde ausgewählt
{

}


void MainWindow::on_pBmulti_clicked()           //Button Multiplayer wurde ausgewählt
{

}

