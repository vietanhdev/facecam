#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->graphicsView->setScene(new QGraphicsScene(this));
  ui->graphicsView->scene()->addItem(&pixmap);
  connect(ui->captureBtn, SIGNAL (released()),this, SLOT (capture()));
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::capture() {
    QMessageBox::critical(
        this, "Hello", "Test ");
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
