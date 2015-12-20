#include <iostream>

#include <gtest/gtest.h>

#include <opencv2/core/core.hpp>

#include "src/common/neighbourhood.h"
#include "src/common/neighbourhoodfactory.h"
#include "src/mathtools/seededsegmentation.h"

using namespace cv;
using namespace std;

/**
 * Creates an input image having foreground and background
 * 
 * @param size the size of the image 
 *
 * @return A square input image of size size x size.
 *
 * TODO this method can be used in an utility class for testing
 */
Mat createTestInputImage(unsigned int size) {
    Mat inputImage = Mat::zeros(size, size, CV_32FC3);

    unsigned int foregroundSize = ((double)size / 2);

    for (unsigned int i = 0; i < foregroundSize; i++) {
        for (unsigned int j = 0; j < foregroundSize; j++) {
            inputImage.at<Vec3f>(i, j) = cv::Point3f(1, 1, 1);
        }
    }

    return inputImage;
}

/**
 * Creates a background image for testing
 *
 * @param the size of the image
 *
 * @returns A binary image with seeds for background
 */
Mat createTestBackground(unsigned int size) {
    Mat_<bool> backgroundImage = Mat::zeros(size, size, CV_32FC1);

    backgroundImage.at<bool>(0, 0) = 1;

    return backgroundImage;
}

/**
 * Creates a foreground image for testing
 *
 * @param the size of the image
 *
 * @returns A binary image with seeds for foreground
 */
Mat createTestForeground(unsigned int size) {
    int middle = size/2;
    Mat_<bool> foregroundImage = Mat::zeros(size, size, CV_32FC1);

    foregroundImage.at<bool>(middle, middle) = 1;

    return foregroundImage;
}

/**
 * Testing if the result of the segment function in SeededSegmentation class is
 * working correctly.
 */
TEST(SeededSegmentationTest, SegmentImageCorrectly) {
    const unsigned int size = 10;
    const double beta = 400;
    Mat inputImage = createTestInputImage(size);
    Mat backgroundImage = createTestBackground(size);
    Mat foregroundImage = createTestForeground(size);

    SeededSegmentation segmenter;

    Neighbourhood neighbourhood = 
        NeighbourhoodFactory::createNeighbourhood(
            NeighbourhoodFactory::N8);

    Mat result = 
        segmenter.segment(
            inputImage, backgroundImage, foregroundImage, neighbourhood, beta);

    result = result / 255; // over 255 since it is the maximum value after thresholding

    GTEST_ASSERT_EQ(norm(result - (1 - inputImage)), 0);
}