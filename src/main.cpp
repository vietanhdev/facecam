#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>

std::string expand_user(std::string path) {
  if (!path.empty() && path[0] == '~') {
    assert(path.size() == 1 || path[1] == '/');  // or other error handling
    char const* home = getenv("HOME");
    if (home || ((home = getenv("USERPROFILE")))) {
      path.replace(0, 1, home);
    }
    else {
      char const *hdrive = getenv("HOMEDRIVE"),
        *hpath = getenv("HOMEPATH");
      assert(hdrive);  // or other error handling
      assert(hpath);
      path.replace(0, 1, std::string(hdrive) + hpath);
    }
  }
  return path;
}

int main(int argc, char *argv[])
{
  
    std::cout << expand_user("~/hello/sds dd.p") << std::endl;
    std::cout << "Hello" << std::endl;

	QCoreApplication::addLibraryPath(".");

    QApplication a(argc, argv);
    MainWindow w;

    

    w.show();
    w.showCam();

    return a.exec();
}
