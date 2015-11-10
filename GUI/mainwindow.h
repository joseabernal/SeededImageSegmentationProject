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

    private:
        DisplayWindow disp;
        DisplayWindow dispResult;

        SegmentationEventHandler* comm;

        QImage inputImage;
        QImage result;

        cv::Mat seed0;
        cv::Mat seed1;
                
        unsigned int currentSeed;

        Ui::MainWindow *ui;

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        
        void paintSeed(const unsigned int i, const unsigned int j);


    private slots:
        void handleResult(const QImage& image);

        void on_pushButtonOpenImage_clicked();

        void on_pushButtonSeed1_clicked();

        void on_pushButtonSeed2_clicked();

        void on_pushButtonSegmentImage_clicked();
};

#endif // MAINWINDOW_H