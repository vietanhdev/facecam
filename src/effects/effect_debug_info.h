#if !defined(EFFECT_DEBUG_INFO_H)
#define EFFECT_DEBUG_INFO_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "timer.h"

class EffectDebugInfo : public ImageEffect {
   private:
    Timer::time_point_t last_draw_time;

    Timer::time_point_t last_calc_fps_time; // Only re-calculate FPS after a certain of time
    Timer::time_duration_t fps_valid_duration = 500; // This variable saves the fps valid duration. After this duration from last_calc_fps_time, we re-calculate fps
    
    float displayed_overall_fps;
    float displayed_detection_fps;
    float displayed_alignment_fps;

    float current_detection_fps;
    float current_alignment_fps;

   public:
    EffectDebugInfo();
    ~EffectDebugInfo();

    void outputFPS(float detection_fps, float alignment_fps);

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO