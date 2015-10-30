#ifndef SEGMENTATION_EVENT_HANDLER_H
#define SEGMENTATION_EVENT_HANDLER_H

#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MathTools/seededsegmentation.h"

using cv::Mat;

/**
 * This class handles the events of the UI classes.
 *
 * @author Jose Bernal
 */
class SegmentationEventHandler {

    private:
        SeededSegmentation segmenter;

        /**
         * Converts a QImage object to cv::Mat
         *
         * @param image QImage object to convert
         *
         * @return the converted cv::Mat object
         *
         * @see http://stackoverflow.com/questions/17127762/cvmat-to-qimage-and-back
         */
        Mat QImage2Mat(const QImage& image);

        /**
         * Converts a cv::Mat object to QImage
         *
         * @param image cv::Mat object to convert
         *
         * @return the converted QImage object
         *
         * @see http://stackoverflow.com/questions/17127762/cvmat-to-qimage-and-back
         */
        QImage Mat2QImage(const Mat& image);

    protected:

    public:

        SegmentationEventHandler();
        ~SegmentationEventHandler();

        QImage loadImage(const string& filePath);

        QImage segment(
            const QImage& image,
            const QImage& backgroundImage,
            const QImage& foregroundImage,
            const double& beta);
        
        bool saveImage(const QImage& image, const string& filePath);
};

#endif