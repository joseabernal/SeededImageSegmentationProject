#include "segmentationeventhandler.h"

SegmentationEventHandler::SegmentationEventHandler() {
}

SegmentationEventHandler::~SegmentationEventHandler() {

}

Mat SegmentationEventHandler::QImage2Mat(QImage const& src) {
    Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    Mat result;
    cvtColor(tmp, result,CV_BGR2RGB);
    return result;
}

QImage SegmentationEventHandler::Mat2QImage(Mat const& src)
{
    Mat temp;
    cvtColor(src, temp,CV_BGR2RGB);
    QImage dest(
       (const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}

QImage SegmentationEventHandler::loadImage(const string& filePath) {
    return Mat2QImage(imread(filePath, CV_32FC3));
}

QImage SegmentationEventHandler::segment(
    const QImage& img, const QImage& bgImage, const QImage& fgImage, const double& beta) {
    Mat inputImage = QImage2Mat(img);
    Mat backgroundImage = QImage2Mat(bgImage);
    Mat foregroundImage = QImage2Mat(fgImage);

    return Mat2QImage(segmenter.segment(inputImage, backgroundImage, foregroundImage, beta, 0.1));
}

bool SegmentationEventHandler::saveImage(
    const QImage& img, const string& filePath) {
    Mat image = QImage2Mat(img);
    imwrite(filePath, image);

    return true;
}