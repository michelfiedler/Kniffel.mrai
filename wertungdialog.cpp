#include "wertungdialog.h"
#include "ui_wertungdialog.h"
#include <data.h>
#include <QObject>
#include <QLabel>


wertungDialog::wertungDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wertungDialog)
{
    ui->setupUi(this);
}

wertungDialog::~wertungDialog()
{
    delete ui;
}

void wertungDialog::on_buttonBox_accepted()
{
    this->close();
}

