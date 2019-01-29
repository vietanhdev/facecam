#include "utility.h"

namespace ml_cam {

void setLabel(cv::Mat& im, const std::string label, const cv::Point & origin)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.5;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::rectangle(im, origin + cv::Point(0, baseline), origin + cv::Point(text.width, -text.height), cv::Scalar(0,255,0), CV_FILLED);
    cv::putText(im, label, origin, fontface, scale, cv::Scalar(0,0,0), thickness, 8);

}


}