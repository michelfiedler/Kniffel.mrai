#include "wertung2dialog.h"
#include "ui_wertung2dialog.h"
#include <data.h>
#include <QObject>
#include <QLabel>
#include <windows.h>

wertung2Dialog::wertung2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wertung2Dialog)
{
    ui->setupUi(this);
}

wertung2Dialog::~wertung2Dialog()
{
    delete ui;
}

void wertung2Dialog::on_buttonBox_accepted()
{
    this->close();
}
