TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += widgets

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    Funktionen.h \
    FunktionenKI.h \
    bestenliste.h \
    mainwindow.h \
    spieler.h

FORMS += \
    mainwindow.ui
