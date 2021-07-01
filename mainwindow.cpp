#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

