#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QImage>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>

#include <opencv/highgui.h>

#include <cv.h>

/**
 * Class in charge of displaying the images on a window.
 *
 * @see Karl Phillip, https://github.com/karlphillip/GraphicsProgramming
 *
 * @author Rodrigo Daudt
 */
class DisplayWindow : public QMainWindow
{
    Q_OBJECT

    private:
        /**
         * Displayed image
         */
        QImage image;
        
        /**
         * Color of the seed.
         */
        QRgb seedColor;


    public:
        /**
         * Default constructor.
         */
        DisplayWindow();

        /**
         * Class destructor.
         */
        ~DisplayWindow();

        /**
         * Displays the given QImage.
         *
         * @param image image to be displayed.
         */
        void displayImage(const QImage& image);

        /**
         * Sets the color of the seed.
         *
         * @param seedColor seed color to use.
         */
        void setSeedColor(const QRgb seedColor);

        /**
         * Handles the paint events
         *
         * @param event event triggered
         */
        void paintEvent(QPaintEvent* event);

        /**
         * Handles the mouse move events
         *
         * @param event event triggered
         */
        void mouseMoveEvent(QMouseEvent *event);

    signals:
        /**
         * Signal emitted when a drawing the seeds.
         */
        void updatePixel(const unsigned int i, const unsigned int j);
};

#endif