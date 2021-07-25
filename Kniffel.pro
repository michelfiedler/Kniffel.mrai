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
        vierspielerdialog.cpp \
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
    vierspielerdialog.h \
    zweispielerdialog.h

FORMS += \
    dreispielerdialog.ui \
    fuenfspielerdialog.ui \
    mainwindow.ui \
    multiplayerdialog.ui \
    sechsspielerdialog.ui \
    siebenspielerdialog.ui \
    singleplayerdialog.ui \
    vierspielerdialog.ui \
    zweispielerdialog.ui

RESOURCES += \
    Resources.qrc
