
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

        // Calculate the position of animation
        int animation_width = face.width * 1.2;

        int left = face.tl().x - (animation_width - face.width) / 2;
        int bottom = face.tl().y - face.width / 5;

        cloud_animation.apply(draw, animation_width, left, bottom);
    }

}