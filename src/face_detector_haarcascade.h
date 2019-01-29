#ifndef FACE_DETECTOR_HAARCASCADE_H
#define FACE_DETECTOR_HAARCASCADE_H

#include "face_detector.h"
#include <string>
#include <iostream>

class FaceDetectorHaarCascade : public FaceDetector {
private:
    const std::string FACE_CASCADE_PATH = "../models/detect_haarcascade/haarcascade_frontalface.xml";
    cv::CascadeClassifier face_cascade;
public:
    FaceDetectorHaarCascade();
    ~FaceDetectorHaarCascade();

    std::vector<LandMarkResult> detect(const cv::Mat & img);
};



#endif