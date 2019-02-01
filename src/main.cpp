#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>
#include "filesystem_include.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    
    w.show();
    w.showCam();

    return a.exec();
}
