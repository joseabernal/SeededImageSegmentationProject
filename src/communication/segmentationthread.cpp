#include "segmentationthread.h"

SegmentationThread::SegmentationThread() {
}

SegmentationThread::~SegmentationThread() {
    wait();
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
    }

    emit sendImage(segmentedImage);
}