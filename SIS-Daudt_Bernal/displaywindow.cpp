// Author: Rodrigo Daudt
// Reference: Karl Phillip, https://github.com/karlphillip/GraphicsProgramming

#include "displaywindow.h"
#include "mainwindow.h"

#include <QPainter>
#include <QDebug>

#include <cv.h>

DisplayWindow::DisplayWindow()
    : _image(NULL)
{
    setWindowTitle(tr("QT Image demo with OpenCV"));
    resize(480, 240);

    seedColor = qRgb(0,0,0);

//    _menu = new QMenu("File");
//    _menu->addAction("Op3n", this, SLOT(_open()));
//    _menu->addSeparator();
//    _menu->addAction("Ex1t", this, SLOT(close()));
//    _menu_bar.addMenu(_menu);

//    setMenuBar(&_menu_bar);
}

DisplayWindow::~DisplayWindow()
{
    if (_image)
        delete _image;
}

void DisplayWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    // When no image has been loaded, there's nothing to draw.
    if (!_image)
        return;

    painter.drawImage(QPoint(0, 0), *_image);

    QWidget::paintEvent(e);
}

void DisplayWindow::displayImage(cv::Mat &img)
{
    // Since OpenCV uses BGR order, we need to convert it to RGB
    cv::cvtColor(img, img, CV_BGR2RGB);

    // _image is created according to video dimensions
    if (_image)
    {
        delete _image;
    }
    _image = new QImage(img.size().width, img.size().height, QImage::Format_RGB888);

    // Copy cv::Mat to QImage
    memcpy(_image->scanLine(0),
           (unsigned char*)img.data,
           _image->width() * _image->height() * img.channels());

    // Set the filename as the window title
    setWindowTitle("Image to be segmented");

    // Resize the window to fit video dimensions
    resize(img.size().width, img.size().height);

    // Mouse move events will occur only when a mouse button is pressed down,
    // unless mouse tracking has been enabled:
//    QWidget::setMouseTracking(true);

    // Trigger paint event to redraw the window
    update();
}

//void DisplayWindow::keyPressEvent(QKeyEvent* event)
//{
//    switch (event->key())
//    {
//        // ESC: exit application
//        case Qt::Key_Escape:
//        {
//            close();
//        }
//        break;
//    }
//}

void DisplayWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!_image)
        return;

    QPoint pos = event->pos();
    if (pos.x() < 0 || pos.x() >= _image->width())
        return;
    if (pos.y() < 0 || pos.y() >= _image->height())
        return;



//    QString pos_x;
//    pos_x = pos_x.setNum(pos.x());

//    QString pos_y;
//    pos_y = pos_y.setNum(pos.y());

//    QColor pixel(_image->pixel(pos));

    int x = pos.x();
    int y = pos.y();
    int w = _image->width();
    int h = _image->height();

    for(int i=-5;i<=5;i++)
        for(int j=-5;j<=5;j++)
            if(x+i>=0 && x+i<w && y+j>=0 && y+j<h)
                _image->setPixel(QPoint(x+i,y+j),seedColor);

    (*parent).paintSeed(x,y,w,h);

    update();

//    int r = pixel.red();
//    int g = pixel.green();
//    int b = pixel.blue();

//    QString pixel_info = pos_x + "," + pos_y + " R:" + QString().setNum(r) +
//                                               " G:" + QString().setNum(g) +
//                                               " B:" + QString().setNum(b);

    // TODO: set pixel info on status bar instead of window title
    //this->statusBar()->setStatusTip(pixel_info);

//    setWindowTitle(pixel_info);

//    qDebug() << "cvImage::mouseMoveEvent " <<  pixel_info;
}

//void DisplayWindow::_close()
//{
//    emit closed();
//}

void DisplayWindow::setSeedColor(QRgb newColor)
{
    seedColor = newColor;
    return;
}

void DisplayWindow::setParent(MainWindow* p)
{
    parent = p;
    return;
}
