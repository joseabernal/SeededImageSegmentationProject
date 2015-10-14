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

    // Open image with opencv
    cv::Mat inputImage = cv::imread(imagePath.toStdString());

    cv::namedWindow("Displaying chosen image");
    cv::imshow("Displaying chosen image", inputImage);

    // Trying to handle events on window
    //cv::setMouseCallback("Displaying chosen image", onMouse, 0);

    //TODO: Do I need a destructor for namedWindow?

//    Old stuff, opens image in main window as Qt object
//    QPixmap chosenImage (imagePath)
//    ui->label->setPixmap(chosenImage);
    //Adding comment to test git, delete as soon as possible
}
