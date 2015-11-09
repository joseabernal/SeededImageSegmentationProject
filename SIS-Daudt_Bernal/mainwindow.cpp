#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentSeed = 0;
    disp.setParent(this);

    seed0 = cv::Mat::zeros(256,256,CV_8UC1);
    seed1 = cv::Mat::zeros(256,256,CV_8UC1);
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

    if (imagePath.isEmpty()) // Do nothing if filename is empty
        return;


    inputImage = cv::imread(imagePath.toStdString());
    if (inputImage.empty())
        return;

    int rows = inputImage.rows;
    int cols = inputImage.cols;

    seed0 = cv::Mat::zeros(rows,cols,CV_8UC1);
    seed1 = cv::Mat::zeros(rows,cols,CV_8UC1);



    disp.show();
    disp.move(100,100);
    disp.displayImage(inputImage);

    return;
}

void MainWindow::paintSeed(int r,int c, int w, int h)
{
    if(currentSeed==0)
    {
        for(int i=-5;i<=5;i++)
            for(int j=-5;j<=5;j++)
                if(c+i>=0 && c+i<w && r+j>=0 && r+j<h)
                    seed0.at<unsigned int>(c+i,r+j) = 1;
    } else
    {
        for(int i=-5;i<=5;i++)
            for(int j=-5;j<=5;j++)
                if(c+i>=0 && c+i<w && r+j>=0 && r+j<h)
                    seed1.at<unsigned int>(c+i,r+j) = 1;
    }

    return;
}


void MainWindow::on_pushButtonSeed1_clicked()
{
    currentSeed = 0;
    disp.setSeedColor(qRgb(0,0,0));
    return;
}

void MainWindow::on_pushButtonSeed2_clicked()
{
    currentSeed = 0;
    disp.setSeedColor(qRgb(255,255,255));
    return;
}


void MainWindow::on_pushButtonSegmentImage_clicked()
{
    result = comm.segment(inputImage,seed0,seed1,(double)400);

    dispResult.show();
    dispResult.move(100,100);
    dispResult.displayImage(result);

    return;
}
