#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentSeed = 0;
    disp.setParent(this);

    seed0 = cv::Mat::zeros(256, 256, CV_8UC1);
    seed1 = cv::Mat::zeros(256, 256, CV_8UC1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonOpenImage_clicked()
{
    //Image location dialog
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        "/home",
        tr("Image Files (*.png *.jpg *.bmp *.tiff)"));

    if (imagePath.isEmpty()) { // Do nothing if filename is empty
        return;
    }

    inputImage = comm.loadImage(imagePath.toStdString());
    
    if (inputImage.isNull()) {
        return;
    }

    seed0 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);
    seed1 = cv::Mat::zeros(inputImage.height(), inputImage.width(), CV_8UC1);

    disp.show();
    disp.move(100, 100);
    disp.displayImage(inputImage);

    return;
}

void MainWindow::paintSeed(const unsigned int i, const unsigned int j)
{
    if (currentSeed == 0)
    {
        seed0.at<bool>(i, j) = 1.0;
    }
    else {
        seed1.at<bool>(i, j) = 1.0;
    }

    return;
}


void MainWindow::on_pushButtonSeed1_clicked()
{
    currentSeed = 0;
    disp.setSeedColor(qRgb(0, 0, 0));
    return;
}

void MainWindow::on_pushButtonSeed2_clicked()
{
    currentSeed = 1;
    disp.setSeedColor(qRgb(255, 255, 255));
    return;
}


void MainWindow::on_pushButtonSegmentImage_clicked()
{
    result = comm.segment(inputImage, seed0, seed1, 400.0);

    dispResult.show();
    dispResult.move(100, 100);
    dispResult.displayImage(result);

    return;
}