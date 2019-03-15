#if !defined(ANIMATION_H)
#define ANIMATION_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "timer.h"
#include "filesystem_include.h"

class Animation {
   private:
   		cv::Mat dummy_frame;
        std::vector<cv::Mat> frames;
        size_t current_frame_index = 0; // Index of current frame in vector `frames`
        Timer::time_duration_t animation_frame_duration = 0; // Time to change animation
        Timer::time_point_t last_animation_time; // The last time the animation was changed
   public:
    Animation();
    ~Animation();

    void addFrame(const std::string & img_path);
    const cv::Mat & getFrame(size_t index);
    const cv::Mat & getFrame();
    void setFPS(float fps);

    // Code from: http://jepsonsblog.blogspot.com/2012/10/overlay-transparent-image-in-opencv.html
    // NOTE: background must be in BGR, foreground must be in GBRA format (png image)
    void overlayImage(const cv::Mat& background, const cv::Mat& foreground,
                  cv::Mat& output, cv::Point2i location);

    cv::Mat rotateImage(const cv::Mat & img, double angle);

    // Apply animation into image at position cv::Rect rect
    void apply(cv::Mat& draw, int animation_width, int left, int bottom, double angle = 0);

};


#endif  // ANIMATION_H
