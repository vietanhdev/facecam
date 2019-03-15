#if !defined(EFFECT_FEATHER_HAT_H)
#define EFFECT_FEATHER_HAT_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "animation.h"

class EffectFeatherHat : public ImageEffect {
   private:
        Animation feather_hat_animation;
   public:
    EffectFeatherHat();
    ~EffectFeatherHat();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO

