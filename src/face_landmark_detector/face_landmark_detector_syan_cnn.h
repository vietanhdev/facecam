#ifndef FACE_LANDMARK_DETECTOR_SYAN_CNN_H
#define FACE_LANDMARK_DETECTOR_SYAN_CNN_H

#include "face_landmark_detector.h"
#include <string>
#include <iostream>
#include "opencv2/face.hpp"


class FaceLandmarkDetectorSyanCNN : public FaceLandmarkDetector {
private:
    const std::string TENSORFLOW_WEIGHT_FILE =
        "./models/alignment_syan_cnn/AN02.pb";
    cv::dnn::Net face_model;

public:
    FaceLandmarkDetectorSyanCNN();
    ~FaceLandmarkDetectorSyanCNN();
    std::vector<int> getFacialPoints(const cv::Mat & image);

    std::vector<LandMarkResult> detect(const cv::Mat & img, std::vector<LandMarkResult> & faces);
};



#endif