#if !defined(UTILITY_H)
#define UTILITY_H

#include <opencv2/opencv.hpp>


namespace ml_cam {

void setLabel(cv::Mat& im, const std::string label, const cv::Point & origin);
std::string expand_user(std::string path);

}

#endif // UTILITY_H
