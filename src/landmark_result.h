#ifndef LANDMARK_RESULT_H
#define LANDMARK_RESULT_H


#include "opencv2/opencv.hpp"
#include <algorithm>    // std::copy

class LandMarkResult
{
private:
    cv::Rect face_rect;
    float face_rect_confidence;
    std::vector<cv::Point2f> landmark;

    // Indices of face parts.
    // The first element is start index. The second element is the last index
    const int MOUTH_IDX[2] = { 48, 68 };
    const int RIGHT_EYE_BROW_IDX[2] = { 17, 22 };
    const int LEFT_EYE_BROW_IDX[2] = { 22, 27 };
    const int RIGHT_EYE_IDX[2] = { 36, 42 };
    const int LEFT_EYE_IDX[2] = { 42, 48 };
    const int NOSE_IDX[2] = { 27, 35 };
    const int JAW_IDX[2] = { 0, 17 };

public:
    LandMarkResult(/* args */);
    ~LandMarkResult();

    // Copy assignment, copy-and-swap form
    LandMarkResult& operator=(LandMarkResult other)
    {
        face_rect = other.face_rect;
        face_rect_confidence = other.face_rect_confidence;
        landmark = other.landmark;
        return *this;
    }

    cv::Rect getFaceRect() const;
    float getFaceRectConfidence();
    void setFaceRect(const cv::Rect & face);
    void setFaceRect(const cv::Rect & face_rect, float confidence);

    const std::vector<cv::Point2f> & getFaceLandmark();
    void setFaceLandmark(std::vector<cv::Point2f> & landmark);

    std::vector<cv::Point2f> getMouth();
    std::vector<cv::Point2f> getRightEyeBrow();
    std::vector<cv::Point2f> getLeftEyeBrow();
    std::vector<cv::Point2f> getRightEye();
    std::vector<cv::Point2f> getLeftEye();
    std::vector<cv::Point2f> getNose();
    std::vector<cv::Point2f> getJaw();

};

#endif