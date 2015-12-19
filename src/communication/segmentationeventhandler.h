#ifndef SEGMENTATION_EVENT_HANDLER_H
#define SEGMENTATION_EVENT_HANDLER_H

#include <QImage>
#include <QMetaType>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "src/common/imagetypeconverter.h"
#include "src/common/neighbourhood.h"
#include "src/common/neighbourhoodfactory.h"
#include "src/mathtools/seededsegmentation.h"

#include "segmentationthread.h"

using cv::Mat;

/**
 * This class handles the events of the UI classes.
 *
 * @author Jose Bernal
 */
class SegmentationEventHandler : public QObject {
    Q_OBJECT

    private:
        SegmentationThread* segmentationThread;

    protected:

    public:

        /**
         * Default constructor.
         */
        SegmentationEventHandler();

        /**
         * Class destructor.
         */
        ~SegmentationEventHandler();

        /**
         * Load image on filePath
         *
         * @param filePath path of the file to load
         *
         * @return QImage loaded image
         */
        QImage loadImage(const string filePath);

        /**
         * Calls the seededsegmentation class with the given inputs.
         *
         * @param image image to be segmented
         * @param backgroundImage background image to segment
         * @param foregroundImage foreground image to segment
         * @param beta tuning variable
         */
        void segment(
            const QImage& image,
            const Mat& backgroundImage,
            const Mat& foregroundImage,
            const double beta);
        
        /**
         * Returns the image with the boundary according to the segmentation
         * image.
         *
         * @param inputImage input image
         * @param segmentedImage binary image containing the segmentation of 
         *  input image
         * 
         * @return an image containing the respective boundaries.
         */
        QImage obtainImageWithBoundary(
            const QImage& inputImage, const QImage& segmentedImage);

        /**
         * Load image on filePath
         *
         * @param image image to save
         * @param filePath path to save the image
         *
         * @return true if the process was successful
         */
        bool saveImage(const QImage& image, const string filePath);

    private slots:

        /**
         * Slot handling the result after segmentation.
         */
        void handleResult(const Mat& finalImage);

    signals:

        /**
         * Signal emitted when the result after segmentation is obtained.
         */
        void sendImage(const QImage& finalImage);
};

#endif