#ifndef SEEDINPUTWINDOW_H
#define SEEDINPUTWINDOW_H

#include "displaywindow.h"

/**
 * Class in charge of input of segmentation seeds
 *
 * @see Karl Phillip, https://github.com/karlphillip/GraphicsProgramming
 *
 * @author Rodrigo Daudt
 */
class SeedInputWindow : public DisplayWindow
{
    Q_OBJECT

    private:
        /**
         * Color of the seed.
         */
        QRgb seedColor;


    public:
        /**
         * Default constructor.
         */
        SeedInputWindow();

        /**
         * Class destructor.
         */
        ~SeedInputWindow();

        /**
         * Sets the color of the seed.
         *
         * @param seedColor seed color to use.
         */
        void setSeedColor(const QRgb seedColor);

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

#endif // SEEDINPUTWINDOW_H
