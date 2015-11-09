#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ui_mainwindow.h"

#include "displaywindow.h"
#include "Communication/segmentationeventhandler.h"

class DisplayWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintSeed(int,int,int,int);


private slots:
    void on_pushButtonOpenImage_clicked();

    void on_pushButtonSeed1_clicked();

    void on_pushButtonSeed2_clicked();

    void on_pushButtonSegmentImage_clicked();

private:
    DisplayWindow disp;
    DisplayWindow dispResult;
    SegmentationEventHandler comm;
    cv::Mat inputImage;
    cv::Mat seed0;
    cv::Mat seed1;
    cv::Mat result;
    int currentSeed;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
