#ifndef SINGLEPLAYERDIALOG_H
#define SINGLEPLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class singleplayerDialog;
}

class singleplayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit singleplayerDialog(QWidget *parent = nullptr);
    ~singleplayerDialog();

private slots:
    void on_buttonBox_rejected();

    void on_tW_SpielstandSingle_cellClicked(int row, int column);

public slots:
    void neuWaehlen();
    void einsenGewaehlt();
    void zweienGewaehlt();
    void dreienGewaehlt();
    void vierenGewaehlt();
    void fuenfenGewaehlt();
    void sechsenGewaehlt();
    void dreierpaschGewaehlt();
    void viererpaschGewaehlt();
    void fullhouseGewaehlt();
    void klstrasseGewaehlt();
    void grstrasseGewaehlt();
    void kniffelGewaehlt();
    void chanceGewaehlt();


public:
signals:
    void besetzt();
    void wahlEinsen();
    void wahlZweien();
    void wahlDreien();
    void wahlVieren();
    void wahlFuenfen();
    void wahlSechsen();
    void wahlDreierpasch();
    void wahlViererpasch();
    void wahlFullHouse();
    void wahlKlStrasse();
    void wahlGrStrasse();
    void wahlKniffel();
    void wahlChance();

private:
    Ui::singleplayerDialog *ui;
};

#endif // SINGLEPLAYERDIALOG_H
