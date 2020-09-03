#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T16:39:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_e4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        fenetre.cpp \
    dbmanager.cpp \
    inscription.cpp \
    menus.cpp \
    gestion_ticket.cpp \
    ajout_ticket.cpp \
    gestion_uti.cpp \
    infoticket.cpp

HEADERS  += fenetre.h \
    dbmanager.h \
    inscription.h \
    menus.h \
    gestion_ticket.h \
    ajout_ticket.h \
    gestion_uti.h \
    infoticket.h

FORMS    += fenetre.ui \
    inscription.ui \
    connexion.ui \
    menus.ui \
    gestion_ticket.ui \
    ajout_ticket.ui \
    gestion_uti.ui \
    infoticket.ui
