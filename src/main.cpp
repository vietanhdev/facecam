#include <QApplication>
#include <stdlib.h>
#include <iostream>
#include "filesystem_include.h"
#include "framelesswindow.h"
#include "DarkStyle.h"
#include "mainwindow.h"
#include "file_storage.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Init file storage
    ml_cam::FileStorage fs;
    fs.initStorage();

    // Style our application with custom dark style
    a.setStyle(new DarkStyle);

    // Create frameless window (and set windowState or title)
    FramelessWindow framelessWindow;
    framelessWindow.setWindowTitle("FaceCam");
    framelessWindow.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));
    
    // Create our mainwindow instance
    MainWindow *mainWindow = new MainWindow;

    // Add the mainwindow to our custom frameless window
    framelessWindow.setContent(mainWindow);
    framelessWindow.show();
    mainWindow->showCam();

    return a.exec();
}
