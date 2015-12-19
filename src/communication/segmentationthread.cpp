#include "segmentationthread.h"

SegmentationThread::SegmentationThread() {
}

SegmentationThread::~SegmentationThread() {
    wait(); //useful?
}

void SegmentationThread::processImage(
    const Mat& inputImageIn,
    const Mat& backgroundImageIn,
    const Mat& foregroundImageIn,
    const Neighbourhood& neighbourhoodIn,
    const double betaIn) {
    inputImage = inputImageIn;
    backgroundImage = backgroundImageIn;
    foregroundImage = foregroundImageIn;
    neighbourhood = neighbourhoodIn;
    beta = betaIn;
}

void SegmentationThread::run() {
    Mat segmentedImage;
    bool sucessful = true;
    try {
        segmentedImage = segmenter.segment(
            SegmentationUtility::normalizedImage(inputImage),
            backgroundImage,
            foregroundImage,
            neighbourhood,
            beta);
    }
    catch(std::exception& e) {
        qDebug() << "Error detected in the process. "
            << e.what()
            << ". "
            << "Sending empty image" << endl;

        sucessful = false;
    }

    if (sucessful) {
        emit sendImage(
            SegmentationUtility::obtainImageWithBoundary(inputImage, segmentedImage));
    }
    else {
        emit sendImage(segmentedImage);   
    }
}