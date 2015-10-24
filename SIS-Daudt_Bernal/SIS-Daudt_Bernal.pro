#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:44:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SIS-Daudt_Bernal
TEMPLATE = app

#added manually
INCLUDEPATH += /usr/include/opencv

#added manually
LIBS += -L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        mainwindow.cpp \
    displaywindow.cpp

HEADERS  += mainwindow.h \
    displaywindow.h

FORMS    += mainwindow.ui
