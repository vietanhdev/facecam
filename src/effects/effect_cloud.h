#if !defined(EFFECT_CLOUD_H)
#define EFFECT_CLOUD_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "animation.h"

class EffectCloud : public ImageEffect {
   private:
        Animation cloud_animation;
   public:
    EffectCloud();
    ~EffectCloud();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO

