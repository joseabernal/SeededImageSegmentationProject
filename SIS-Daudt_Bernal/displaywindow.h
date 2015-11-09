#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QKeyEvent>
#include <QPainter>

#include <opencv/highgui.h>

//#include "mainwindow.h"

class MainWindow;

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    DisplayWindow();
    ~DisplayWindow();

    void setParent(MainWindow*);
    void displayImage(cv::Mat &);
    void paintEvent(QPaintEvent* e);
//    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSeedColor(QRgb);

private:
    MainWindow* parent;
    QImage* _image;
    QRgb seedColor;

//private slots:
//    void _open();

//protected:
//    void _close();

//signals:
//    void closed();
};

#endif // DISPLAYWINDOW_H
