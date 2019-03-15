#if !defined(EFFECT_PINK_GLASSES_H)
#define EFFECT_PINK_GLASSES_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "animation.h"

class EffectPinkGlasses : public ImageEffect {
   private:
        Animation pink_glasses_animation;
   public:
    EffectPinkGlasses();
    ~EffectPinkGlasses();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO

