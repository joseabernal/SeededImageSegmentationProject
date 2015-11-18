#include "seedinputwindow.h"

SeedInputWindow::SeedInputWindow() {
    setWindowTitle(tr("Seed Input Window"));
    resize(480, 240);

    seedColor = qRgb(0,0,0);
}

SeedInputWindow::~SeedInputWindow() {
}

void SeedInputWindow::mouseMoveEvent(QMouseEvent *event) {
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

void SeedInputWindow::setSeedColor(QRgb newColor) {
    seedColor = newColor;
    return;
}
