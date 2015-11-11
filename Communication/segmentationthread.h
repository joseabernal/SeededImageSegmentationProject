#ifndef SEGMENTATION_THREAD_H
#define SEGMENTATION_THREAD_H

#include <QThread>

#include <opencv2/core/core.hpp>

#include "Common/neighbourhood.h"
#include "MathTools/seededsegmentation.h"

using cv::Mat;

/**
 * This class is in charge of the segmentation process.
 *
 * @see http://doc.qt.io/qt-5/qtcore-threads-queuedcustomtype-renderthread-h.html
 *
 * @author Jose Bernal
 */
class SegmentationThread : public QThread {
    Q_OBJECT

    private:

        /**
         * The beta value to use in the calculations.
         */
        double beta;

        /**
         * SeededSegmentation object to use for segmenting the images.
         */
        SeededSegmentation segmenter;
        
        /**
         * The input image to segment.
         */
        Mat inputImage;

        /**
         * The image representing the seeds of background.
         */
        Mat backgroundImage;

        /**
         * The image representing the seeds of foreground.
         */
        Mat foregroundImage;

        /**
         * The neighbourhood to use on the segmentation.
         */
        Neighbourhood neighbourhood;

    protected:

        /**
         * Calls the segment method of SeededSegmentation.
         */
        void run();

    public:

        /**
         * Default constructor.
         */
        SegmentationThread();

        /**
         * Class destructor.
         */
        ~SegmentationThread();

        /**
         * Calls the seededsegmentation class with the given inputs. This call
         * is asynchronous. The result of this process is given by the slot 
         * 
         * @param image image to be segmented
         * @param backgroundImage background image to segment
         * @param foregroundImage foreground image to segment
         * @param beta tuning variable
         */
        void processImage(
            const Mat& inputImage,
            const Mat& backgroundImage,
            const Mat& foregroundImage,
            const Neighbourhood& neighbourhood,
            const double beta);

    signals:

        /**
         * Signal containing a the matrix with the segmentation
         */
        void sendImage(const Mat& image);
};

#endif