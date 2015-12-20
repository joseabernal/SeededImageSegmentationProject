#include "displaywindow.h"

DisplayWindow::DisplayWindow() {
    setWindowTitle(tr("Segmentation Result"));
    resize(480, 240);
}

DisplayWindow::~DisplayWindow() {
}

void DisplayWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    // When no image has been loaded, there's nothing to draw.
    if (image.isNull()) {
        throw UserInputException("Empty image cannot be displayed");
    }

    painter.drawImage(QPoint(0, 0), image);

    QWidget::paintEvent(e);
}

void DisplayWindow::displayImage(const QImage &src) {
    image = src; 

    // Resize the window to fit video dimensions
    resize(src.width(), src.height());

    update();
}
