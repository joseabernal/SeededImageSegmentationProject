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

/**
 *
 *
 * @see Karl Phillip, https://github.com/karlphillip/GraphicsProgramming
 *
 * @author Rodrigo Daudt
 */
class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    DisplayWindow();
    ~DisplayWindow();

    void setParent(MainWindow*);
    void displayImage(const QImage&);
    void paintEvent(QPaintEvent* e);
//    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSeedColor(QRgb);

private:
    MainWindow* parent;
    
    QImage _image;
    
    QRgb seedColor;

//private slots:
//    void _open();

//protected:
//    void _close();

//signals:
//    void closed();
};

#endif // DISPLAYWINDOW_H