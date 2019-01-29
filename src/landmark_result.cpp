#include "landmark_result.h"

LandMarkResult::LandMarkResult(/* args */) {
}

LandMarkResult::~LandMarkResult() {
}

void LandMarkResult::setFaceRect(const cv::Rect & face_rect) {
    this->face_rect = face_rect;
}

cv::Rect LandMarkResult::getFaceRect() {
    return face_rect;
}
