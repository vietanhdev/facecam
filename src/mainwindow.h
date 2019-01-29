#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>

#include <memory>
#include "opencv2/opencv.hpp"

#include "face_detector_haarcascade.h"
#include "face_detector_ssd_resnet10.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showCam();

protected:
    void closeEvent(QCloseEvent *event);
    void loadEffects();

private slots:
    void captureBtn_clicked();
    void recordBtn_clicked();
    void faceDetectorSelector_activated();
    void showAboutBox();
    
private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;

    // Face detectors
    std::vector<std::shared_ptr<FaceDetector>> face_detectors;
    int current_face_detector_index = -1; // Index of current face detector method in face_detectors

public:
    void loadFaceDetectors();

};

#endif // MAINWINDOW_H
