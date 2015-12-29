#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "displaywindow.h"
#include "seedinputwindow.h"
#include "ui_mainwindow.h"
#include "src/exceptions/userinputexception.h"
#include "src/communication/segmentationeventhandler.h"

namespace Ui {
    class MainWindow;
}

/**
 * Main window of the application.
 *
 * @author Rodrigo Daudt
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

    private:

        /**
         * Ui of the application
         */
        Ui::MainWindow *ui;

        /**
         * SeedInputWindow instance aiming to display the input image and seeds.
         */
        SeedInputWindow* inp;

        /**
         * DisplayWindow instance aiming to display the segmentation result - BW
         */
        DisplayWindow* disp_bw;

        /**
         * DisplayWindow instance aiming to display the segmentation result - contour
         */
        DisplayWindow* disp_c;


        /**
         * Event handler of segmentation-related tasks.
         */
        SegmentationEventHandler* comm;

        /**
         * The input image.
         */
        QImage inputImage;

        /**
         * The result image.
         */
        QImage result;

        /**
         * The original image with segmentation contours
         */
        QImage contourImage;

        /**
         * Matrix of the seeds of foreground
         */
        cv::Mat seed0;

        /**
         * Matrix of the seeds of background
         */
        cv::Mat seed1;
                
        /**
         * Number of the current seed.
         */
        unsigned int currentSeed;

    public:

        /**
         * Default constructor
         *
         * @param parent parent component
         */
        explicit MainWindow(QWidget *parent = 0);

        /**
         * Class destructor.
         */
        ~MainWindow();

    private slots:

        /**
         * When the sendImage signal is emitted from the communication layer,
         * this method is triggered.
         *
         * @param image Result of the segmentation to be displayed
         */
        void handleResult(const QImage& image);

        /**
         * When the updatePixel signal is emitted from the DisplayWindow class,
         * this method is triggered.
         *
         * @param i row of the pixel to be updated
         * @param j col of the pixel to be updated
         */
        void handleUpdatePixel(const unsigned int i, const unsigned int j);

        /**
         * Method triggered when the open image button is clicked.
         */
        void on_pushButtonOpenImage_clicked();

        /**
         * Method triggered when the seed 1 button is clicked.
         */
        void on_pushButtonSeed1_clicked();

        /**
         * Method triggered when the seed 2 button is clicked.
         */
        void on_pushButtonSeed2_clicked();

        /**
         * Method triggered when the segment button is clicked.
         */
        void on_pushButtonSegmentImage_clicked();
};

#endif
