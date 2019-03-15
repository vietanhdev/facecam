#ifndef FACE_LANDMARK_DETECTOR_H
#define FACE_LANDMARK_DETECTOR_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "landmark_result.h"
#include "filesystem_include.h"

class FaceLandmarkDetector {
private:
    std::string detector_name;
public:
    FaceLandmarkDetector();
    ~FaceLandmarkDetector();

    // This function will receive results from face detection phase
    // then add the results of face alignment phase 
    virtual std::vector<LandMarkResult> detect(const cv::Mat & img, std::vector<LandMarkResult> & faces) = 0;
    std::string getDetectorName();
    void setDetectorName(std::string);

};

#endif