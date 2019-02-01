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
    connect(ui->faceDetectorSelector, SIGNAL(activated(int)), this,
            SLOT(faceDetectorSelector_activated()));
    connect(ui->effectList, SIGNAL(itemSelectionChanged()), this,
            SLOT(effectList_onselectionchange()));

    // load effects to use in this project
    loadEffects();

    // Load Detectors
    loadFaceDetectors();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::captureBtn_clicked() {
    QMessageBox::critical(this, "NOT IMPLEMENTED",
                          "This function hasn't been implemented");
}

void MainWindow::recordBtn_clicked() {
    QMessageBox::critical(this, "NOT IMPLEMENTED",
                          "This function hasn't been implemented");
}

void MainWindow::faceDetectorSelector_activated() {
    current_face_detector_index =
        ui->faceDetectorSelector
            ->itemData(ui->faceDetectorSelector->currentIndex())
            .toInt();
}

void MainWindow::effectList_onselectionchange() {
    QList<QListWidgetItem *> selected_effects = ui->effectList->selectedItems();

    // Save selected effects
    selected_effect_indices.clear();
    for (int i = 0; i < selected_effects.count(); ++i) {
        selected_effect_indices.push_back(
            selected_effects[i]->data(Qt::UserRole).toInt());
    }
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
            std::vector<LandMarkResult> landmarks;
            if (current_face_detector_index >= 0) {
                landmarks =
                    face_detectors[current_face_detector_index]->detect(frame);

            } else {  // Clear old results
                landmarks.clear();
            }

            for (size_t i = 0; i < selected_effect_indices.size(); ++i) {
                if (selected_effect_indices[i] >= 0) {
                    image_effects[selected_effect_indices[i]]->apply(frame,
                                                                     landmarks);
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
    
    // SSD - ResNet10 detector
    face_detectors.push_back(
        std::shared_ptr<FaceDetector>(new FaceDetectorSSDResNet10()));

    // Haar cascade detector
    face_detectors.push_back(
        std::shared_ptr<FaceDetector>(new FaceDetectorHaarCascade()));

    // Add detectors to selector box of GUI
    for (size_t i = 0; i < face_detectors.size(); ++i) {
        ui->faceDetectorSelector->addItem(
			QString::fromUtf8(face_detectors[i]->getDetectorName().c_str()),
            QVariant(static_cast<int>(i)));
    }
    // Add None option
    ui->faceDetectorSelector->addItem("None", -1);

    current_face_detector_index = 0;  // set default face detector method
}

void MainWindow::loadEffects() {

    // Effect: Debug
    image_effects.push_back(
        std::shared_ptr<ImageEffect>(new EffectDebugInfo()));

    // Effect: Raining Cloud
    image_effects.push_back(
        std::shared_ptr<ImageEffect>(new EffectCloud()));

    // Add "No Effect"
    QListWidgetItem *new_effect = new QListWidgetItem(
        QIcon(":/resources/images/no-effect.png"), "No Effect");
    new_effect->setData(Qt::UserRole, QVariant(static_cast<int>(-1)));
    ui->effectList->addItem(new_effect);

    for (size_t i = 0; i < image_effects.size(); ++i) {
		std::string effect_name = image_effects[i]->getName();
		QString effect_name_qs = QString::fromUtf8(effect_name.c_str());
        QListWidgetItem *new_effect = new QListWidgetItem(
            QIcon(QPixmap::fromImage(Mat2QImage(image_effects[i]->getIcon()))),
			effect_name_qs);
        new_effect->setData(Qt::UserRole, QVariant(static_cast<int>(i)));
        ui->effectList->addItem(new_effect);
    }
}

QImage MainWindow::Mat2QImage(cv::Mat const &src) {
    cv::Mat temp;                     // make the same cv::Mat
    cvtColor(src, temp, cv::COLOR_BGR2RGB);  // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step,
                QImage::Format_RGB888);
    dest.bits();  // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format
    // format )
    return dest;
}

cv::Mat MainWindow::QImage2Mat(QImage const &src) {
    cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar *)src.bits(),
                src.bytesPerLine());
    cv::Mat
        result;  // deep copy just in case (my lack of knowledge with open cv)
    cvtColor(tmp, result, cv::COLOR_BGR2RGB);
    return result;
}
