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

    segmentationOccurred = false;

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

    // Do nothing if filename is empty
    if (imagePath.isEmpty()) {
        return;
    }

    // Load image
    inputImage = comm->loadImage(imagePath.toStdString());
    
    // If no image is loaded and exception is thrown
    if (inputImage.isNull()) {
        throw UserInputException("The image could not be opened.");
    }

    // Adjust seed matrices for the appropriate size
    seed0 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);
    seed1 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);

    // Display loaded image
    inp->show();
    inp->move(500, 100);
    inp->displayImage(inputImage);
}

void MainWindow::handleUpdatePixel(const unsigned int i, const unsigned int j) {
    // Paint seed matrices according to mouse event and current selected seed
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

    // Register that segmentation has occured
    segmentationOccurred = true;
}

void MainWindow::on_pushButtonSeed1_clicked() {
    // Tells program that the current input is for seed 1
    currentSeed = 0;
    inp->setSeedColor(qRgb(0, 0, 0));
}

void MainWindow::on_pushButtonSeed2_clicked() {
    // Tells program that the current input is for seed 2
    currentSeed = 1;
    inp->setSeedColor(qRgb(255, 255, 255));
}

void MainWindow::on_pushButtonSegmentImage_clicked() {
    // Gets beta from the user, default value of 400.0
    double beta = QInputDialog::getDouble(this,"Beta","Please choose a value for beta:",400.0,1);

    // Calls image segmentation
    if (!inputImage.isNull()) {
        comm->segment(inputImage, seed0, seed1, beta);
    }
    else {
        throw UserInputException("An image should be selected first.");
    }
}

void MainWindow::on_pushButton_saveBinary_clicked()
{
    // Checks if there are segmentation results ready
    if(!segmentationOccurred)
        return;

    // Save black and white result
    QString path = QFileDialog::getSaveFileName();
    bool successful_save;
    successful_save = comm->saveImage(result, path);
}

void MainWindow::on_pushButton_saveContour_clicked()
{
    // Checks if there are segmentation results ready
    if(!segmentationOccurred)
        return;

    // Save contour result
    QString path = QFileDialog::getSaveFileName();
    bool successful_save;
    successful_save = comm->saveImage(contourImage, path);
}
