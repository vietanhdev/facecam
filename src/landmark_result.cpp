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

cv::Rect LandMarkResult::getFaceRect() const {
    return face_rect;
}

float LandMarkResult::getFaceRectConfidence() {
    return face_rect_confidence;
}

const std::vector<cv::Point2f> & LandMarkResult::getFaceLandmark() {
    return landmark;
}

void LandMarkResult::setFaceLandmark(std::vector<cv::Point2f> & landmark){
    this->landmark = landmark;
}


bool LandMarkResult::haveLandmark() {
    return !landmark.empty();
}


std::vector<cv::Point2f> LandMarkResult::getMouth() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[MOUTH_IDX[0]], &landmark[MOUTH_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getRightEyeBrow() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[RIGHT_EYE_BROW_IDX[0]], &landmark[RIGHT_EYE_BROW_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getLeftEyeBrow() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[LEFT_EYE_BROW_IDX[0]], &landmark[LEFT_EYE_BROW_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getRightEye() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[RIGHT_EYE_IDX[0]], &landmark[RIGHT_EYE_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getLeftEye() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[LEFT_EYE_IDX[0]], &landmark[LEFT_EYE_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getNose() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[NOSE_IDX[0]], &landmark[NOSE_IDX[1]]);
    return sub_landmark;
}
std::vector<cv::Point2f> LandMarkResult::getJaw() {
    if (landmark.empty()) return landmark;
    std::vector<cv::Point2f> sub_landmark(&landmark[JAW_IDX[0]], &landmark[JAW_IDX[1]]);
    return sub_landmark;
}

