#ifndef FACE_DETECTOR_CASCADE_H
#define FACE_DETECTOR_CASCADE_H

#include "face_detector.h"
#include <string>
#include <iostream>

class FaceDetectorCascade : public FaceDetector {
private:
    cv::CascadeClassifier face_cascade;
public:
    FaceDetectorCascade(std::string detector_name, std::string model_path);
    ~FaceDetectorCascade();

    std::vector<LandMarkResult> detect(const cv::Mat & img);
};



#endif