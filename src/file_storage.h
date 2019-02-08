
#include <iostream>
#include "filesystem_include.h"
#include "utility.h"

namespace ml_cam {

class FileStorage {
   private:
    const fs::path DATA_FOLDER_NAME = "mLearningCam";
    const fs::path PHOTO_FOLDER_NAME = "Photos";
    const fs::path VIDEO_FOLDER_NAME = "Videos";
    fs::path DATA_FOLDER;
    fs::path PHOTO_FOLDER;
    fs::path VIDEO_FOLDER;

   public:
    FileStorage();
    ~FileStorage();

    fs::path getDataPath();
    fs::path getPhotoPath();
    fs::path getVideoPath();
    void initStorage();
};

}  // namespace ml_cam