#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>
#include <filesystem>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	std::filesystem::path cp = std::filesystem::current_path();
	std::cout << cp << std::endl;

    
    w.show();
    w.showCam();

    return a.exec();
}
