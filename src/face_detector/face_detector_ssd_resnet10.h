#ifndef FACE_DETECTOR_SDD_RESNET10_H
#define FACE_DETECTOR_SDD_RESNET10_H

#include <iostream>
#include <string>
#include "face_detector.h"

class FaceDetectorSSDResNet10 : public FaceDetector {
   private:
    const std::string TENSORFLOW_CONFIG_FILE =
        "./models/detect_ssd_resnet10/opencv_face_detector.pbtxt";
    const std::string TENSORFLOW_WEIGHT_FILE =
        "./models/detect_ssd_resnet10/opencv_face_detector_uint8.pb";
    cv::dnn::Net face_model;

   public:
    FaceDetectorSSDResNet10();
    ~FaceDetectorSSDResNet10();

    std::vector<LandMarkResult> detect(const cv::Mat& img);
};


#endif