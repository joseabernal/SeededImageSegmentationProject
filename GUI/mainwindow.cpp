#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    currentSeed = 0;
    seed0 = cv::Mat::zeros(256, 256, CV_8UC1);
    seed1 = cv::Mat::zeros(256, 256, CV_8UC1);

    comm = new SegmentationEventHandler();
    inp = new SeedInputWindow();
    disp = new DisplayWindow();

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
    delete disp;
    delete inp;
    comm = 0;
    inp = 0;
    disp = 0;
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
        return;
    }

    seed0 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);
    seed1 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);

    inp->show();
    inp->move(100, 100);
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
    disp->show();
    disp->move(100, 100);
    disp->displayImage(result);
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
    comm->segment(inputImage, seed0, seed1, 400.0);
}
