#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QKeyEvent>

#include <opencv/highgui.h>

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    DisplayWindow();
    ~DisplayWindow();

    void displayImage(cv::Mat &);
    void paintEvent(QPaintEvent* e);
//    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    //QMenuBar _menu_bar;
    //QMenu* _menu;
    QImage* _image;

//private slots:
//    void _open();

//protected:
//    void _close();

//signals:
//    void closed();
};

#endif // DISPLAYWINDOW_H
