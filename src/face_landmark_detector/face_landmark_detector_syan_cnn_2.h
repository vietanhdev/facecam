#ifndef FACE_LANDMARK_DETECTOR_SYAN_CNN_2_H
#define FACE_LANDMARK_DETECTOR_SYAN_CNN_2_H

#include "face_landmark_detector.h"
#include <string>
#include <iostream>
#include "opencv2/face.hpp"


class FaceLandmarkDetectorSyanCNN2 : public FaceLandmarkDetector {
private:
<<<<<<< HEAD
=======
    const std::string MODEL_PATH = "./models/alignment_syan_cnn/AN01.model";
   const std::string TENSORFLOW_CONFIG_FILE =
        "./models/alignment_syan_cnn/AN02.pbtxt";
    const std::string TENSORFLOW_WEIGHT_FILE =
        "./models/alignment_syan_cnn/AN02.pb";
    cv::dnn::Net face_model;
>>>>>>> master

public:
    FaceLandmarkDetectorSyanCNN2();
    ~FaceLandmarkDetectorSyanCNN2();
    std::vector<int> getFacialPoints(const cv::Mat & image);

    std::vector<LandMarkResult> detect(const cv::Mat & img, std::vector<LandMarkResult> & faces);
};



#endif