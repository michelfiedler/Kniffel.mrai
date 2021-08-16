#include "wertung2dialog.h"
#include "ui_wertung2dialog.h"
#include <data.h>
#include <QObject>
#include <QLabel>
#include <windows.h>

wertung2dialog::wertung2dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wertung2dialog)
{
    ui->setupUi(this);
}

wertung2dialog::~wertung2dialog()
{
    delete ui;
}

void wertung2dialog::on_buttonBox_accepted()
{
    this->close();
}
