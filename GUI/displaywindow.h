#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QImage>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>

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

    protected:
        /**
         * Displayed image
         */
        QImage image;


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
         * Handles the paint events
         *
         * @param event event triggered
         */
        void paintEvent(QPaintEvent* event);
};

#endif
