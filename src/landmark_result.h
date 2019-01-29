#ifndef LANDMARK_RESULT_H
#define LANDMARK_RESULT_H


#include "opencv2/opencv.hpp"

class LandMarkResult
{
private:
    cv::Rect face_rect;
public:
    LandMarkResult(/* args */);
    ~LandMarkResult();

    cv::Rect getFaceRect();
    void setFaceRect(const cv::Rect & face);
};

#endif