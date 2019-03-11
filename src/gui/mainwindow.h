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

#include <SDL.h>

#include <mutex>
#include <memory>
#include "opencv2/opencv.hpp"

#include "face_detector_haarcascade.h"
#include "face_detector_ssd_resnet10.h"

#include "image_effect.h"
#include "effect_debug_info.h"
#include "effect_cloud.h"

#include "file_storage.h"


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
    void openLibraryBtn_clicked();
    void faceDetectorSelector_activated();
    void effectList_onselectionchange();
    void showAboutBox();
    
private:
    Ui::MainWindow *ui;

    // Current image
    // When user click "Capture", we take photo here then have it
    // to [Photos] folder
    cv::Mat current_img;
    std::mutex current_img_mutex;

    // File Storage
    ml_cam::FileStorage fs;


    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;

    // Face detectors
    std::vector<std::shared_ptr<FaceDetector>> face_detectors;
    int current_face_detector_index = -1; // Index of current face detector method in face_detectors

    // Photo effects
    std::vector<std::shared_ptr<ImageEffect>> image_effects;
    std::vector<int> selected_effect_indices; // Indices of selected effect in image_effects

public:
    void loadFaceDetectors();
    void setCurrentImage(const cv::Mat & img);
    cv::Mat getCurrentImage();
    void playShutter();
};

#endif // MAINWINDOW_H
