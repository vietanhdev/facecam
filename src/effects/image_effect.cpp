
#include "image_effect.h"

ImageEffect::ImageEffect(std::string name, std::string icon_path) {
    this->name = name;
    this->icon = cv::imread(icon_path, -1);
}

ImageEffect::~ImageEffect() {}

void ImageEffect::setName(std::string name) {
    this->name = name;
}
std::string ImageEffect::getName() {
    return name;
}

void ImageEffect::setIcon(const cv::Mat & icon) {
    this->icon = icon.clone();
}
const cv::Mat ImageEffect::getIcon() {
    return icon;
}
