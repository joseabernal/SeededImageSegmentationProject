#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    currentSeed = 0;
    seed0 = cv::Mat::zeros(256, 256, CV_8UC1);
    seed1 = cv::Mat::zeros(256, 256, CV_8UC1);

    comm = new SegmentationEventHandler();
    inp = new SeedInputWindow();
    disp_bw = new DisplayWindow();
    disp_c = new DisplayWindow();

    connect(
        comm,
        SIGNAL(sendImage(const QImage&)),
        this,
        SLOT(handleResult(const QImage&)));

    connect(
        inp,
        SIGNAL(updatePixel(const unsigned int, const unsigned int)),
        this,
        SLOT(handleUpdatePixel(const unsigned int, const unsigned int)));
}

MainWindow::~MainWindow() {
    delete ui;
    delete comm;
    delete disp_bw;
    delete disp_c;
    delete inp;
    comm = 0;
    inp = 0;
    disp_bw = 0;
    disp_c = 0;
}

void MainWindow::on_pushButtonOpenImage_clicked() {
    //Image location dialog
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        "./",
        tr("Image Files (*.png *.jpg *.bmp *.tiff)"));

    if (imagePath.isEmpty()) { // Do nothing if filename is empty
        return;
    }

    inputImage = comm->loadImage(imagePath.toStdString());
    
    if (inputImage.isNull()) {
        throw UserInputException("The image could not be opened.");
    }

    seed0 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);
    seed1 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);

    inp->show();
    inp->move(500, 100);
    inp->displayImage(inputImage);
}

void MainWindow::handleUpdatePixel(const unsigned int i, const unsigned int j) {
    if (currentSeed == 0) {
        seed0.at<bool>(i, j) = 1.0;
    }
    else {
        seed1.at<bool>(i, j) = 1.0;
    }
}

void MainWindow::handleResult(const QImage& image) {
    result = image;

    // Draw contour lines over segmented image
    contourImage = comm->obtainImageWithBoundary(inputImage, result);

    // Display binary segmentation
    disp_bw->show();
    disp_bw->move(100, 100);
    disp_bw->displayImage(result);

    // Display image with overlaid segmentation contour
    disp_c->show();
    disp_c->move(300, 300);
    disp_c->displayImage(contourImage);
}

void MainWindow::on_pushButtonSeed1_clicked() {
    currentSeed = 0;
    inp->setSeedColor(qRgb(0, 0, 0));
}

void MainWindow::on_pushButtonSeed2_clicked() {
    currentSeed = 1;
    inp->setSeedColor(qRgb(255, 255, 255));
}

void MainWindow::on_pushButtonSegmentImage_clicked() {
    if (!inputImage.isNull()) {
        comm->segment(inputImage, seed0, seed1, 400.0);
    }
    else {
        throw UserInputException("An image should be selected first.");
    }
}

void MainWindow::on_pushButton_saveBinary_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    bool whatever;
    whatever = result.save(path);
}

void MainWindow::on_pushButton_saveContour_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    bool whatever;
    whatever = contourImage.save(path);
}
