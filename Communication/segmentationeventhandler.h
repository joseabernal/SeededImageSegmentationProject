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
         * @see http://answers.opencv.org/question/9075/how-do-i-save-qimage-in-cvmat/
         */
        Mat QImage2Mat(const QImage& image);

        /**
         * Converts a cv::Mat object to QImage
         *
         * @param image cv::Mat object to convert
         *
         * @return the converted QImage object
         *
         * @see http://answers.opencv.org/question/9075/how-do-i-save-qimage-in-cvmat/
         */
        QImage Mat2QImage(const Mat& image);

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
        QImage loadImage(const string& filePath);

        /**
         * Calls the seededsegmentation class with the given inputs.
         *
         * @param image image to be segmented
         * @param backgroundImage background image to segment
         * @param foregroundImage foreground image to segment
         * @param beta tuning variable
         *
         * @return Mat loaded image
         */
        Mat segment(
            const Mat& image,
            const Mat& backgroundImage,
            const Mat& foregroundImage,
            const double& beta);
        
        /**
         * Load image on filePath
         *
         * @param image image to save
         * @param filePath path to save the image
         *
         * @return true if the process was successful
         */
        bool saveImage(const QImage& image, const string& filePath);
};

#endif