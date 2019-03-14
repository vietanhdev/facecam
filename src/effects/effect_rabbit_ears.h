#if !defined(EFFECT_RABBIT_EARS_H)
#define EFFECT_RABBIT_EARS_H

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"
#include "animation.h"

class EffectRabbitEars : public ImageEffect {
   private:
        Animation rabbit_ears_animation;
   public:
    EffectRabbitEars();
    ~EffectRabbitEars();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO

