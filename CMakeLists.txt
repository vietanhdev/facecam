#Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Specify project title
project(FaceCam)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

find_package(SDL2 REQUIRED sdl2)

# Take care of Qt dependencies
find_package(Qt5 COMPONENTS Core Gui Widgets Test Concurrent REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

include_directories(
    "src"
    "src/effects"
    "src/face_detector"
    "src/face_landmark_detector"
    "src/gui"
    "src/gui/framelesswindow"
    ${SDL2_INCLUDE_DIRS}
)

# add required source, header, ui and resource files
add_executable(${PROJECT_NAME} 
    "src/main.cpp"
    "src/utility.cpp"
    "src/file_storage.cpp"
    "src/gui/mainwindow.cpp"
    "src/gui/mainwindow.ui"
    "src/landmark_result.cpp"

    "src/face_detector/face_detector.cpp"
    "src/face_detector/face_detector_cascade.cpp"
    "src/face_detector/face_detector_ssd_resnet10.cpp"
    "src/face_detector/face_detector_ssd_resnet10.cpp"
    
    "src/face_landmark_detector/face_landmark_detector.cpp"
    "src/face_landmark_detector/face_landmark_detector_kazemi.cpp"
    "src/face_landmark_detector/face_landmark_detector_lbf.cpp"

    "src/face_landmark_detector/face_landmark_detector_syan_cnn.cpp"
    "src/face_landmark_detector/face_landmark_detector_syan_fnn.cpp"

    "src/effects/image_effect.cpp"
    "src/effects/effect_debug_info.cpp"
    "src/effects/effect_cloud.cpp"
    "src/effects/effect_rabbit_ears.cpp"
    "src/effects/effect_feather_hat.cpp"
    "src/effects/effect_tiger.cpp"
    "src/effects/effect_pink_glasses.cpp"

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
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES} ${OpenCV_LIBS} ${CPP_FS_LIB} ${SDL2_LIBRARIES})

# Copy files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/images $<TARGET_FILE_DIR:${PROJECT_NAME}>/images)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/models $<TARGET_FILE_DIR:${PROJECT_NAME}>/models)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/sounds $<TARGET_FILE_DIR:${PROJECT_NAME}>/sounds)



# Compile qimgv if not in Windows
if (NOT WIN32)
    add_subdirectory(qimgv)
endif (NOT WIN32)

