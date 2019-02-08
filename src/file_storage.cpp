#include "file_storage.h"

using namespace ml_cam;

FileStorage::FileStorage() {
    DATA_FOLDER = fs::path(getHomePath()) / DATA_FOLDER_NAME;
    PHOTO_FOLDER = DATA_FOLDER / PHOTO_FOLDER_NAME;
    VIDEO_FOLDER = DATA_FOLDER / VIDEO_FOLDER_NAME;
}

FileStorage::~FileStorage() {}

void FileStorage::initStorage() {
    std::cout << "Data Folder: " << getDataPath() << std::endl;
    std::cout << "Photos Folder: " << getPhotoPath() << std::endl;
    std::cout << "Videos Folder: " << getVideoPath() << std::endl;

    // *** Create directories

    // Photos
    if (fs::exists(getPhotoPath()) && !fs::is_directory(getPhotoPath())) {
        std::cerr << "Photos folder path is not a directory: " << getPhotoPath()
                  << std::endl;
        exit(-1);
    } else if (!fs::exists(getPhotoPath())) {
        // Create photos directory if not exist
        fs::create_directories(getPhotoPath());

        if (!fs::exists(getPhotoPath())) {
            std::cerr << "Could not create directory: " << getPhotoPath()
                  << std::endl;
            exit(-1);
        }
    }

    // Videos
    if (fs::exists(getVideoPath()) && !fs::is_directory(getVideoPath())) {
        std::cerr << "Videos folder path is not a directory: " << getVideoPath()
                  << std::endl;
        exit(-1);
    } else if (!fs::exists(getVideoPath())) {
        // Create photos directory if not exist
        fs::create_directories(getVideoPath());

        if (!fs::exists(getVideoPath())) {
            std::cerr << "Could not create directory: " << getVideoPath()
                  << std::endl;
            exit(-1);
        }
    }
}

fs::path FileStorage::getDataPath() { return DATA_FOLDER; }

fs::path FileStorage::getPhotoPath() { return PHOTO_FOLDER; }

fs::path FileStorage::getVideoPath() { return VIDEO_FOLDER; }