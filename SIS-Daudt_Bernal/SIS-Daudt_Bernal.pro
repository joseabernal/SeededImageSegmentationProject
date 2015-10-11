#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:44:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SIS-Daudt_Bernal
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv2 #added manually

LIBS += -L/usr/lib -lopencv_core -lopencv_highgui #added manually

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
