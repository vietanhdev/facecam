#ifndef IMAGE_EFFECT_H
#define IMAGE_EFFECT_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "landmark_result.h"

class ImageEffect {
   private:
    std::string name;
    cv::Mat icon; // To use in GUI
   public:
    ImageEffect(std::string name, std::string icon_path);
    ~ImageEffect();

    void setName(std::string name);
    std::string getName();

    void setIcon(const cv::Mat & icon);
    const cv::Mat getIcon();

    virtual void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) = 0;

};

#endif  // IMAGE_EFFECT_H
