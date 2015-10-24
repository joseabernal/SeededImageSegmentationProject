#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    disp.show();
    disp.move(100,100);
    disp.displayImage(inputImage);


}

