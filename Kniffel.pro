TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += widgets

SOURCES += \
        Funktionen.cpp \
        FunktionenKI.cpp \
        bestenliste.cpp \
        data.cpp \
        dreispielerdialog.cpp \
        fuenfspielerdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        multiplayerdialog.cpp \
        sechsspielerdialog.cpp \
        siebenspielerdialog.cpp \
        singleplayerdialog.cpp \
        spieler.cpp \
        spielmodusmultidialog.cpp \
        vierspielerdialog.cpp \
        wertungdialog.cpp \
        zweispielerdialog.cpp

HEADERS += \
    Funktionen.h \
    FunktionenKI.h \
    bestenliste.h \
    data.h \
    dreispielerdialog.h \
    fuenfspielerdialog.h \
    mainwindow.h \
    multiplayerdialog.h \
    sechsspielerdialog.h \
    siebenspielerdialog.h \
    singleplayerdialog.h \
    spieler.h \
    spielmodusmultidialog.h \
    vierspielerdialog.h \
    wertungdialog.h \
    zweispielerdialog.h

FORMS += \
    dreispielerdialog.ui \
    fuenfspielerdialog.ui \
    mainwindow.ui \
    multiplayerdialog.ui \
    sechsspielerdialog.ui \
    siebenspielerdialog.ui \
    singleplayerdialog.ui \
    spielmodusmultidialog.ui \
    vierspielerdialog.ui \
    wertungdialog.ui \
    zweispielerdialog.ui

RESOURCES += \
    Resources.qrc
