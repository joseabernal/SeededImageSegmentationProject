#include "segmentationeventhandler.h"

SegmentationEventHandler::SegmentationEventHandler() {
    segmentationThread = new SegmentationThread();

    qRegisterMetaType< cv::Mat >("Mat");
    connect(
        segmentationThread,
        SIGNAL(sendImage(const Mat&)),
        this,
        SLOT(handleResult(const Mat&)));
}

SegmentationEventHandler::~SegmentationEventHandler() {
    if (segmentationThread->isRunning()) {
        segmentationThread->terminate();        
    }

    delete segmentationThread;
}

QImage SegmentationEventHandler::loadImage(const string filePath) {
    QImage dest;
    dest.load(filePath.c_str());

    return dest;
}

void SegmentationEventHandler::segment(
    const QImage& img,
    const Mat& backgroundImage,
    const Mat& foregroundImage,
    const double beta) {
    Mat inputImage = ImageTypeConverter::convertQImage2Mat(img);

    Neighbourhood neighbourhood = 
        NeighbourhoodFactory::createNeighbourhood(
            NeighbourhoodFactory::N8);

    segmentationThread->processImage(
        inputImage, backgroundImage, foregroundImage, neighbourhood, beta);
    segmentationThread->start();
}

QImage SegmentationEventHandler::obtainImageWithBoundary(
    const QImage& img, const QImage& segImg) {
    Mat inputImage = ImageTypeConverter::convertQImage2Mat(img);
    Mat segmentedImage = ImageTypeConverter::convertQImage2Mat(segImg);

    Mat result = 
        SegmentationUtility::obtainImageWithBoundary(inputImage, segmentedImage);

    return ImageTypeConverter::convertMat2QImage(result);
}

bool SegmentationEventHandler::saveImage(
    const QImage& img, const string filePath) {
    QImage image = img;
    image.save(filePath.c_str());

    return true;
}

void SegmentationEventHandler::handleResult(const Mat& finalImage) {
    emit sendImage(ImageTypeConverter::convertMat2QImage(finalImage));
}