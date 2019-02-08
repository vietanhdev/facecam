#Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Specify project title
project(ml-cam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
find_package(Qt5 COMPONENTS Core Gui Widgets Test Concurrent REQUIRED)

include_directories(
    "src"
    "src/effects"
    "src/face_detector"
    "src/gui"
    "src/gui/framelesswindow"
)

# add required source, header, ui and resource files
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    "src/utility.cpp"
    "src/gui/mainwindow.cpp"
    "src/gui/mainwindow.ui"
    "src/landmark_result.cpp"
    "src/face_detector/face_detector.cpp"
    "src/face_detector/face_detector_haarcascade.cpp"
    "src/face_detector/face_detector_ssd_resnet10.cpp"
    "src/effects/image_effect.cpp"
    "src/effects/effect_debug_info.cpp"
    "src/effects/effect_cloud.cpp"
    "src/timer.cpp"
    "src/effects/animation.cpp"
    "resources.qrc"
    "src/gui/framelesswindow.qrc"
    "src/gui/darkstyle.qrc"
    "src/gui/DarkStyle.cpp"
    "src/gui/framelesswindow/framelesswindow.cpp"
    "src/gui/framelesswindow/windowdragger.cpp"
    "src/gui/framelesswindow/framelesswindow.ui"
)

ADD_LIBRARY(
    ${PROJECTNAME} STATIC
    ${HEADER_FILES}
)

# Use C++ 17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    set (CPP_FS_LIB "stdc++fs")
endif()

# link required libs
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS} ${CPP_FS_LIB})

# Copy files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:${PROJECT_NAME}>/images)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/models $<TARGET_FILE_DIR:${PROJECT_NAME}>/models)