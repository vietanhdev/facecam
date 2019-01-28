#Specify the minimum version of CMake (3.1 is currently recommended by Qt)
cmake_minimum_required(VERSION 3.1)

# Specify project title
project(ml-cam)

# To automatically run MOC when building (Meta Object Compiler)
set(CMAKE_AUTOMOC ON)

# To automatically run UIC when building (User Interface Compiler)
set(CMAKE_AUTOUIC ON)

# To automatically run RCC when building (Resource Compiler)
set(CMAKE_AUTORCC ON)

# Specify OpenCV folder, and take care of dependencies and includes
#set(OpenCV_DIR "path_to_opencv")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Take care of Qt dependencies
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# add required source, header, ui and resource files
add_executable(${PROJECT_NAME} "main.cpp" "mainwindow.h" "mainwindow.cpp" "mainwindow.ui" "resources.qrc")

# link required libs
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS})
