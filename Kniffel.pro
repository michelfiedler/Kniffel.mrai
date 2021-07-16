TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += widgets

SOURCES += \
        Funktionen.cpp \
        bestenliste.cpp \
        data.cpp \
        dreispielerdialog.cpp \
        main.cpp \
        mainwindow.cpp \
        multiplayerdialog.cpp \
        singleplayerdialog.cpp \
        vierspielerdialog.cpp \
        zweispielerdialog.cpp

HEADERS += \
    Funktionen.h \
    FunktionenKI.h \
    bestenliste.h \
    data.h \
    dreispielerdialog.h \
    mainwindow.h \
    multiplayerdialog.h \
    singleplayerdialog.h \
    spieler.h \
    vierspielerdialog.h \
    zweispielerdialog.h

FORMS += \
    dreispielerdialog.ui \
    mainwindow.ui \
    multiplayerdialog.ui \
    singleplayerdialog.ui \
    vierspielerdialog.ui \
    zweispielerdialog.ui
