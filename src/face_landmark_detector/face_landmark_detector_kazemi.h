#ifndef FACE_LANDMARK_DETECTOR_KAZEMI_H
#define FACE_LANDMARK_DETECTOR_KAZEMI_H

#include "face_landmark_detector.h"
#include <string>
#include <iostream>
#include "opencv2/face.hpp"

class FaceLandmarkDetectorKazemi : public FaceLandmarkDetector {
private:
    const std::string MODEL_PATH = "./models/alignment_kazemi/face_landmark_model.dat";
    cv::Ptr<cv::face::FacemarkKazemi> facemark;

public:
    FaceLandmarkDetectorKazemi();
    ~FaceLandmarkDetectorKazemi();

    std::vector<LandMarkResult> detect(const cv::Mat & img, std::vector<LandMarkResult> & faces);
};



#endif