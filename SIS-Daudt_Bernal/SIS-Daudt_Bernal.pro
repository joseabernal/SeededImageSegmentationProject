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
INCLUDEPATH += /usr/include/opencv /usr/include/eigen3

#added manually
LIBS += -L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        mainwindow.cpp \
    displaywindow.cpp \
    ../MathTools/seededsegmentation.cpp \
    ../Exceptions/exception.cpp \
    ../Exceptions/mathexception.cpp \
    ../Exceptions/userinputexception.cpp \
    ../Communication/segmentationeventhandler.cpp \
    ../Common/neighbourhood.cpp \
    ../Common/neighbourhoodfactory.cpp

HEADERS  += mainwindow.h \
    displaywindow.h \
    ../MathTools/seededsegmentation.h \
    ../Exceptions/exception.h \
    ../Exceptions/mathexception.h \
    ../Exceptions/userinputexception.h \
    ../Communication/segmentationeventhandler.h \
    ../Common/neighbourhood.h \
    ../Common/neighbourhoodfactory.h

FORMS    += mainwindow.ui
