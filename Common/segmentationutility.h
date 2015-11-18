#ifndef SEGMENTATION_UTILITY_H
#define SEGMENTATION_UTILITY_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using cv::Mat;

/**
 * This class present a set of utilities for polishing the segmentation result.
 *
 * @author Jose Bernal
 */
class SegmentationUtility
{
    public:

        /**
         * Computes the boundary of the given binary image.
         *
         * @param inputImage binary image to be processed.
         *
         * @return boundary obtained for the given image.
         */
        static Mat computeBoundary(const Mat& inputImage);

        /**
         * Multiplies the given image by the given scalar.
         *
         * @param inputImage image to be processed.
         * @param scalar scalar to multiply
         *
         * @return the result of the multiplication
         */
        static Mat multiply(const Mat& inputImage, const cv::Scalar& scalar);

        /**
         * Obtain the normalized image from 0 to 1.
         *
         * @param inputImage image to be processed.
         *
         * @return the normalized image
         */
        static Mat normalizedImage(const Mat& inputImage);

        /**
         * Creates an image taking into account the input image and the 
         * segmented image. The result will show the input image and the boundary
         * of the segmented regions.
         *
         * @param inputImage image to be processed.
         * @param segmentedImage image resulting from the segmentation process.
         *
         * @return input image with boundary of the segmented regions.
         */
        static Mat obtainImageWithBoundary(
            const Mat& inputImage, const Mat& segmentedImage);
};

#endif