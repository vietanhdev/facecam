#if !defined(EFFECT_TIGER_H)
#define EFFECT_TIGER_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "animation.h"

class EffectTiger : public ImageEffect {
   private:
        Animation tiger_animation;
   public:
    EffectTiger();
    ~EffectTiger();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO

