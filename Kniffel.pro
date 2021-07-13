TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += widgets

SOURCES += \
        bestenliste.cpp \
        data.cpp \
        main.cpp \
        mainwindow.cpp \
        multiplayerdialog.cpp \
        singleplayerdialog.cpp

HEADERS += \
    Funktionen.h \
    FunktionenKI.h \
    bestenliste.h \
    data.h \
    mainwindow.h \
    multiplayerdialog.h \
    singleplayerdialog.h \
    spieler.h

FORMS += \
    mainwindow.ui \
    multiplayerdialog.ui \
    singleplayerdialog.ui
