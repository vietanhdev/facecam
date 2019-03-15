
#include "effect_tiger.h"

EffectTiger::EffectTiger()
    : ImageEffect("Tiger", "images/effects/tiger/icon.png") {

    tiger_animation.setFPS(0);
    tiger_animation.addFrame("images/effects/tiger/tiger.png");

}
EffectTiger::~EffectTiger() {}

void EffectTiger::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();

        // Calculate the position of animation
        int animation_width = face.width * 2.2;

        int left = face.tl().x - (animation_width - face.width) / 2;
        int bottom = face.br().y + animation_width * 0.16;

        tiger_animation.apply(draw, animation_width, left, bottom); 
    }

}

