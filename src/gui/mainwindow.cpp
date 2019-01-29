#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    // Connect buttons
    connect(ui->captureBtn, SIGNAL(released()), this,
            SLOT(captureBtn_clicked()));
    connect(ui->recordBtn, SIGNAL(released()), this, SLOT(recordBtn_clicked()));
    connect(ui->infoBtn, SIGNAL(released()), this, SLOT(showAboutBox()));

    // Option selector events
    connect(ui->faceDetectorSelector,SIGNAL(activated(int)),this,SLOT(faceDetectorSelector_activated()));

    // load effects to use in this project
    loadEffects();

    // Load Detectors
    loadFaceDetectors();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadEffects() {
    ui->effectListWidget->addItem(new QListWidgetItem(
        QIcon(":/resources/images/no-effect.png"), "No effect"));
    ui->effectListWidget->addItem(new QListWidgetItem(
        QIcon(":/resources/images/new-year-hat.png"), "New Year Hat"));
}

void MainWindow::captureBtn_clicked() {
    QMessageBox::critical(this, "NOT IMPLEMENTED",
                          "This function hasn't been implemented");
}

void MainWindow::recordBtn_clicked() {
    QMessageBox::critical(this, "NOT IMPLEMENTED",
                          "This function hasn't been implemented");
}

void MainWindow::faceDetectorSelector_activated() {
    current_face_detector_index = ui->faceDetectorSelector->itemData(ui->faceDetectorSelector->currentIndex()).toInt();
}

void MainWindow::showAboutBox() {
    QMessageBox::about(this, "About Us",
                       "This camera app is built as group project for cource "
                       "Machine Learning & Data Mining at Hanoi University of "
                       "Science and Technology.\nAuthor:\n\t- Viet Anh "
                       "(vietanhdev.com)\n\t- Sy An (github.com/NguyenSyAn)");
}

void MainWindow::showCam() {
    using namespace cv;

    // TODO Guess camera index
    int cameraIndex = 0;

    if (!video.open(cameraIndex)) {
        QMessageBox::critical(
            this, "Camera Error",
            "Make sure you entered a correct camera index,"
            "<br>or that the camera is not being accessed by another program!");
        return;
    }

    Mat frame;
    while (video.isOpened()) {
        video >> frame;
        if (!frame.empty()) {
            // Detect Faces
            if (current_face_detector_index >= 0) {
                std::vector<LandMarkResult> landmarks =
                    face_detectors[current_face_detector_index]->detect(frame);

                // Draw faces to image
                for (size_t i = 0; i < landmarks.size(); ++i) {
                    cv::rectangle(frame, landmarks[i].getFaceRect(), cv::Scalar(0, 255, 0), 2);
                }
            }

            // Show current image to users
            QImage qimg(frame.data, frame.cols, frame.rows, frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (video.isOpened()) {
        video.release();
    }
    QApplication::quit();
    exit(0);
}


// Load face detectors
void MainWindow::loadFaceDetectors() {

    // Haar cascade detector
    face_detectors.push_back(std::shared_ptr<FaceDetector>(new FaceDetectorHaarCascade()));

    // SSD - ResNet10 detector
    face_detectors.push_back(std::shared_ptr<FaceDetector>(new FaceDetectorSSDResNet10()));

    // Add detectors to selector box of GUI
    for (size_t i = 0; i < face_detectors.size(); ++i) {
        ui->faceDetectorSelector->addItem(QString::fromStdString(face_detectors[i]->getDetectorName()), QVariant(static_cast<int>(i)));
    }
    // Add None option
    ui->faceDetectorSelector->addItem("None", -1);

    current_face_detector_index = 0; // set default face detector method
    
}
