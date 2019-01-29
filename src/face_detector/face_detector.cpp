#include "face_detector.h"

FaceDetector::FaceDetector() {}
FaceDetector::~FaceDetector() {}


std::string FaceDetector::getDetectorName() {
    return detector_name;
}
void FaceDetector::setDetectorName(std::string detector_name) {
    this->detector_name = detector_name;
}