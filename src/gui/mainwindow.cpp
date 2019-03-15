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
    connect(ui->openLibraryBtn, SIGNAL(released()), this,
            SLOT(openLibraryBtn_clicked()));

    // Option selector events
    connect(ui->faceDetectorSelector, SIGNAL(activated(int)), this,
            SLOT(faceDetectorSelector_activated()));
    connect(ui->faceLandmarkDetectorSelector, SIGNAL(activated(int)), this,
            SLOT(faceLandmarkDetectorSelector_activated()));
    connect(ui->effectList, SIGNAL(itemSelectionChanged()), this,
            SLOT(effectList_onselectionchange()));

    // load effects to use in this project
    loadEffects();

    // Load Detectors
    loadFaceDetectors();
    loadFaceLandmarkDetectors();

    // Init Audio
    SDL_Init(SDL_INIT_AUDIO);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::playShutter() {
    SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	SDL_LoadWAV("sounds/shutter-fast.wav", &wavSpec, &wavBuffer, &wavLength);
	
	// open audio device
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	// play audio
	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

	// keep window open enough to hear the sound
	SDL_Delay(200);

	// clean up
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void MainWindow::captureBtn_clicked() {
    fs.saveImage(getCurrentImage());

    // *** Update icon of library to current image
    cv::Mat current_img = getCurrentImage();

    // Play sound file
    playShutter();

    // Create icon by cropping
    int width = current_img.cols;
    int height = current_img.rows;
    int padding_x = 0, padding_y = 0;
    int crop_size;
    if (width <= height) {
        crop_size = width;
        padding_y = (height - width) / 2;
    } else {
        crop_size = height;
        padding_x = (width - height) / 2;
    }

    cv::Mat crop =
        current_img(cv::Rect(padding_x, padding_y, crop_size, crop_size));
    cv::cvtColor(crop, crop, cv::COLOR_BGR2RGB);

    cv::Mat white_bg(50, 50, CV_8UC3, cv::Scalar(255, 255, 255));

    // Set icon for library
    QImage btn_icon = QImage((uchar *)crop.data, crop.cols, crop.rows, crop.step,
                            QImage::Format_RGB888);
    QImage btn_white_icon = QImage((uchar *)crop.data, crop.cols, crop.rows, crop.step,
                            QImage::Format_RGB888);
    ui->openLibraryBtn->setIcon(QIcon(QPixmap::fromImage(btn_white_icon)));
    ui->openLibraryBtn->setIcon(QIcon(QPixmap::fromImage(btn_icon)));
}

void MainWindow::recordBtn_clicked() {
    QMessageBox::critical(this, "NOT IMPLEMENTED",
                          "This function hasn't been implemented");
}

void MainWindow::openLibraryBtn_clicked() {
    std::string command;

#if defined(_WIN32)
    command = std::string("explorer ") + (fs.getPhotoPath() / fs.getLastSavedItem()).string();
#else
    command = std::string("./qimgv ") + (fs.getPhotoPath() / fs.getLastSavedItem()).string();
#endif

    std::system(command.c_str());
}

void MainWindow::faceDetectorSelector_activated() {
    current_face_detector_index =
        ui->faceDetectorSelector
            ->itemData(ui->faceDetectorSelector->currentIndex())
            .toInt();
}

void MainWindow::faceLandmarkDetectorSelector_activated() {
    current_face_landmark_detector_index =
        ui->faceLandmarkDetectorSelector
            ->itemData(ui->faceLandmarkDetectorSelector->currentIndex())
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
                       "This camera app is built using C++, Qt, OpenCV "
                       "and Face detection - alignment algorithms to provide "
                       "funny decorations and filters.\n"
                       "Author:\n"
                       "\t- Viet Anh (vietanhdev.com)\n"
                       "Icons made by:\n"
                       "\t- https://www.flaticon.com/authors/smashicons\n"
                       "\t- https://www.flaticon.com/authors/roundicons\n"
                       "\t- https://www.freepik.com/free-vector/bunny-ears-nose-carnival-mask-photo_4015599.htm\n"
                       "\t- https://www.freepik.com/\n");
}

void MainWindow::showCam() {
    using namespace cv;

    // TODO Guess or let user setup camera index
    int cameraIndex = -1;

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
            std::vector<LandMarkResult> faces;
            if (current_face_detector_index >= 0) {
                faces = face_detectors[current_face_detector_index]->detect(frame);

                if (current_face_landmark_detector_index >= 0) {
                    face_landmark_detectors[current_face_landmark_detector_index]->detect(frame, faces);
                }
            } else {  // Clear old results
                faces.clear();
            }

            for (size_t i = 0; i < selected_effect_indices.size(); ++i) {
                if (selected_effect_indices[i] >= 0) {
                    image_effects[selected_effect_indices[i]]->apply(frame,
                                                                     faces);
                }
            }

            setCurrentImage(frame);

            // Show current image to users
            QImage qimg(frame.data, static_cast<int>(frame.cols),
                        static_cast<int>(frame.rows),
                        static_cast<int>(frame.step), QImage::Format_RGB888);
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


// Load face landmark detectors
void MainWindow::loadFaceLandmarkDetectors() {

    // Landmark Kazemi
    face_landmark_detectors.push_back(
        std::shared_ptr<FaceLandmarkDetector>(new FaceLandmarkDetectorKazemi()));

    // Add detectors to selector box of GUI
    for (size_t i = 0; i < face_landmark_detectors.size(); ++i) {
        ui->faceLandmarkDetectorSelector->addItem(
            QString::fromUtf8(face_landmark_detectors[i]->getDetectorName().c_str()),
            QVariant(static_cast<int>(i)));
    }
    // Add None option
    ui->faceLandmarkDetectorSelector->addItem("None", -1);

    current_face_landmark_detector_index = 0;  // set default face detector method
}

void MainWindow::loadEffects() {
    // Effect: Debug
    image_effects.push_back(
        std::shared_ptr<ImageEffect>(new EffectDebugInfo()));

    // Effect: Raining Cloud
    image_effects.push_back(std::shared_ptr<ImageEffect>(new EffectCloud()));

    // Effect: Pink Glasses
    image_effects.push_back(std::shared_ptr<ImageEffect>(new EffectPinkGlasses()));

    // Effect: Rabbit Ears
    image_effects.push_back(std::shared_ptr<ImageEffect>(new EffectRabbitEars()));

    // Effect: Tiger
    image_effects.push_back(std::shared_ptr<ImageEffect>(new EffectTiger()));

    // Effect: Feather Hat
    image_effects.push_back(std::shared_ptr<ImageEffect>(new EffectFeatherHat()));

    // Add "No Effect"
    QListWidgetItem *new_effect = new QListWidgetItem(
        QIcon(":/resources/images/no-effect.png"), "No Effect");
    new_effect->setData(Qt::UserRole, QVariant(static_cast<int>(-1)));
    ui->effectList->addItem(new_effect);

    for (size_t i = 0; i < image_effects.size(); ++i) {
        std::string effect_name = image_effects[i]->getName();
        QString effect_name_qs = QString::fromUtf8(effect_name.c_str());
        QListWidgetItem *new_effect = new QListWidgetItem(
            QIcon(QPixmap::fromImage(
                ml_cam::Mat2QImage(image_effects[i]->getIcon()))),
            effect_name_qs);
        new_effect->setData(Qt::UserRole, QVariant(static_cast<int>(i)));
        ui->effectList->addItem(new_effect);
    }
}

void MainWindow::setCurrentImage(const cv::Mat &img) {
    std::lock_guard<std::mutex> guard(current_img_mutex);
    current_img = img.clone();
}

cv::Mat MainWindow::getCurrentImage() {
    std::lock_guard<std::mutex> guard(current_img_mutex);
    return current_img.clone();
}