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

	// Apply animation into image at position cv::Rect rect
	void apply(cv::Mat & draw, cv::Rect rect);

};


#endif  // ANIMATION_H
