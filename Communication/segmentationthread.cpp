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
    emit sendImage(segmenter.segment(
        inputImage, backgroundImage, foregroundImage, neighbourhood, beta));
}