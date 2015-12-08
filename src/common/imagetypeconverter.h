#ifndef IMAGE_TYPE_CONVERTER_H
#define IMAGE_TYPE_CONVERTER_H

#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using cv::Mat;
using cv::Vec3f;

/**
 * This class present a set of funtionalities for converting images from 
 * one variable type to another. Ej: QImage -> Mat
 *
 * @author Jose Bernal
 */
class ImageTypeConverter
{
    public:
        /**
         * Converts a QImage object to cv::Mat
         *
         * @param image QImage object to convert
         *
         * @return the converted cv::Mat object
         *
         * @see http://answers.opencv.org/question/9075/how-do-i-save-qimage-in-cvmat/
         */
        static Mat convertQImage2Mat(const QImage& image);

        /**
         * Converts a cv::Mat object to QImage
         *
         * @param image cv::Mat object to convert
         *
         * @return the converted QImage object
         *
         * @see http://answers.opencv.org/question/9075/how-do-i-save-qimage-in-cvmat/
         */
        static QImage convertMat2QImage(const Mat& image);
};

#endif