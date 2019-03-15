#include "face_landmark_detector.h"

FaceLandmarkDetector::FaceLandmarkDetector() {}
FaceLandmarkDetector::~FaceLandmarkDetector() {}


std::string FaceLandmarkDetector::getDetectorName() {
    return detector_name;
}
void FaceLandmarkDetector::setDetectorName(std::string detector_name) {
    this->detector_name = detector_name;
}