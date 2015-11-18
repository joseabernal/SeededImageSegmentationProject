#include "displaywindow.h"

DisplayWindow::DisplayWindow() {
    setWindowTitle(tr("Display Window"));
    resize(480, 240);
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
