#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ui_mainwindow.h"

#include "displaywindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonOpenImage_clicked();

private:
    DisplayWindow disp;
    cv::Mat inputImage;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
