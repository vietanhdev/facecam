
#include "effect_cloud.h"

EffectCloud::EffectCloud()
    : ImageEffect("Raining Cloud", "images/effects/cloud/icon.png") {

    cloud_animation.setFPS(6);
    cloud_animation.addFrame("images/effects/cloud/cloud_animation_1/1.png");
    cloud_animation.addFrame("images/effects/cloud/cloud_animation_1/2.png");
    cloud_animation.addFrame("images/effects/cloud/cloud_animation_1/3.png");

}
EffectCloud::~EffectCloud() {}

void EffectCloud::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();
        cloud_animation.apply(draw, face);
    }

}