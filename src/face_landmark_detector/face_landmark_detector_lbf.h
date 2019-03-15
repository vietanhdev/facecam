#ifndef FACE_LANDMARK_DETECTOR_LBF_H
#define FACE_LANDMARK_DETECTOR_LBF_H

#include "face_landmark_detector.h"
#include <string>
#include <iostream>
#include "opencv2/face.hpp"

class FaceLandmarkDetectorLBF : public FaceLandmarkDetector {
private:
    const std::string MODEL_PATH = "./models/alignment_lbf/lbfmodel.yaml";
    cv::Ptr<cv::face::Facemark> facemark;

public:
    FaceLandmarkDetectorLBF();
    ~FaceLandmarkDetectorLBF();

    std::vector<LandMarkResult> detect(const cv::Mat & img, std::vector<LandMarkResult> & faces);
};



#endif