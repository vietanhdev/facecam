#include "landmark_result.h"

LandMarkResult::LandMarkResult(/* args */) {
}

LandMarkResult::~LandMarkResult() {
}

void LandMarkResult::setFaceRect(const cv::Rect & face_rect) {
    this->face_rect = face_rect;
    face_rect_confidence = 1;
}

void LandMarkResult::setFaceRect(const cv::Rect & face_rect, float confidence) {
    this->face_rect = face_rect;
    face_rect_confidence = confidence;
}

cv::Rect LandMarkResult::getFaceRect() {
    return face_rect;
}

float LandMarkResult::getFaceRectConfidence() {
    return face_rect_confidence;
}