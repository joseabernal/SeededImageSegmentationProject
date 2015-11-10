#include "displaywindow.h"

DisplayWindow::DisplayWindow() {
    setWindowTitle(tr("QT Image demo with OpenCV"));
    resize(480, 240);

    seedColor = qRgb(0,0,0);
}

DisplayWindow::~DisplayWindow() {
}

void DisplayWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    // When no image has been loaded, there's nothing to draw.
    if (image.isNull()) {
        return;
    }

    painter.drawImage(QPoint(0, 0), image);

    QWidget::paintEvent(e);
}

void DisplayWindow::displayImage(const QImage &src) {
    image = src; 
    
    // Set the filename as the window title
    setWindowTitle("Image to be segmented");

    // Resize the window to fit video dimensions
    resize(src.width(), src.height());

    update();
}

void DisplayWindow::mouseMoveEvent(QMouseEvent *event) {
    if (image.isNull()) {
        return;
    }

    QPoint pos = event->pos();
    if (pos.x() < 0 || pos.x() >= image.width()) {
        return;
    }
    if (pos.y() < 0 || pos.y() >= image.height()) {
        return;
    }

    int x = pos.x();
    int y = pos.y();
    int w = image.width();
    int h = image.height();

    for(int i = -5; i <= 5; i++) {
        for(int j = -5; j <= 5; j++) {
            if(x + i >= 0 && x + i < w && y + j >= 0 && y + j < h) {
                image.setPixel(QPoint(x + i, y + j), seedColor);
                
                emit updatePixel(y + j, x + i);
            }
        }
    }

    update();
}

void DisplayWindow::setSeedColor(QRgb newColor) {
    seedColor = newColor;
    return;
}