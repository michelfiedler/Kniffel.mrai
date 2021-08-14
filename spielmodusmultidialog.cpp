#include "spielmodusmultidialog.h"
#include "ui_spielmodusmultidialog.h"
#include "data.h"
#include "Funktionen.h"

#include <QObject>
#include <QLabel>
#include <QMessageBox>

spielmodusMultiDialog::spielmodusMultiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spielmodusMultiDialog)
{
    ui->setupUi(this);
}

spielmodusMultiDialog::~spielmodusMultiDialog()
{
    delete ui;
}
