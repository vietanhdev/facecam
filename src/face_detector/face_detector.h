#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "landmark_result.h"
#include "filesystem_include.h"

class FaceDetector {
private:
    std::string detector_name;
public:
    FaceDetector();
    ~FaceDetector();

    virtual std::vector<LandMarkResult> detect(const cv::Mat & img) = 0;
    std::string getDetectorName();
    void setDetectorName(std::string);

};

#endif