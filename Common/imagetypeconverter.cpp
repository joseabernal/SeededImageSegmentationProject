#include "imagetypeconverter.h"

Mat ImageTypeConverter::convertQImage2Mat(const QImage& src) {
    unsigned int height = src.height();
    unsigned int width = src.width();
    cv::Mat3f dest(height, width);
    
    for (unsigned int i = 0; i < height; i++) {
        cv::Vec3f* destrow = dest[i];
        for (unsigned int j = 0; j < width; j++) {
            QRgb pxl = src.pixel(j, i);
            destrow[j] = cv::Vec3f(qBlue(pxl), qGreen(pxl), qRed(pxl));
        }
    }

    return dest;
}

QImage ImageTypeConverter::convertMat2QImage(const Mat& src)
{
    QImage dest(src.cols, src.rows, QImage::Format_RGB32);
    
    for (unsigned int i = 0; i < src.rows; i++) {
        for (unsigned int j = 0; j < src.cols; j++) {
            Vec3f data = src.at<Vec3f>(i, j);
            QRgb pixel = qRgb((int)(data[2]), (int)(data[1]), (int)(data[0]));
            dest.setPixel(j, i, pixel);
        }
    }

    return dest;
}