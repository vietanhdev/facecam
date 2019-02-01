#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    
    w.show();
    w.showCam();

    return a.exec();
}
