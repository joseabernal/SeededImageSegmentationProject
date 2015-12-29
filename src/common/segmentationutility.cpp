#include "segmentationutility.h"

Mat SegmentationUtility::computeBoundary(const Mat& inputImage) {
    const Mat kernel = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
    
    Mat dest;
    morphologyEx(inputImage, dest, cv::MORPH_GRADIENT, kernel);
    dilate(dest, dest, kernel, cv::Point(-1,-1), 2);

    return dest;
}

Mat SegmentationUtility::multiply(
    const Mat& firstImage, const cv::Scalar& scalar) {
    return firstImage.mul(scalar);
}

Mat SegmentationUtility::normalizedImage(const Mat& inputImage) {
    Mat dest;
    normalize(inputImage, dest, 0.0, 1.0, cv::NORM_MINMAX, CV_32FC3);
    return dest;
}

Mat SegmentationUtility::obtainImageWithBoundary(
    const Mat& inputImage, const Mat& segImage) {
    Mat segmentedImage;
    normalize(segImage, segmentedImage, 0.0, 1.0, cv::NORM_MINMAX, CV_32FC3);
    Mat boundaryImage =
        SegmentationUtility::computeBoundary(segmentedImage);
    boundaryImage = multiply(boundaryImage, cv::Scalar(255, 255, 0));

    Mat contourImage = inputImage;

    return contourImage + contourImage.mul(boundaryImage);
}
