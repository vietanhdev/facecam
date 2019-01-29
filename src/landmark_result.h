#ifndef LANDMARK_RESULT_H
#define LANDMARK_RESULT_H


#include "opencv2/opencv.hpp"

class LandMarkResult
{
private:
    cv::Rect face_rect;
    float face_rect_confidence;

public:
    LandMarkResult(/* args */);
    ~LandMarkResult();

    cv::Rect getFaceRect();
    float getFaceRectConfidence();
    void setFaceRect(const cv::Rect & face);
    void setFaceRect(const cv::Rect & face_rect, float confidence);
};

#endif