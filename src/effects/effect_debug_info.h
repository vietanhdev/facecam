#if !defined(EFFECT_DEBUG_INFO)
#define EFFECT_DEBUG_INFO

#include <opencv2/opencv.hpp>
#include "image_effect.h"
#include "utility.h"

class EffectDebugInfo : public ImageEffect {
   private:
   public:
    EffectDebugInfo();
    ~EffectDebugInfo();

    void apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks);
};

#endif  // EFFECT_DEBUG_INFO
