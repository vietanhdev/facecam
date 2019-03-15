
#include "effect_pink_glasses.h"

EffectPinkGlasses::EffectPinkGlasses()
    : ImageEffect("Pink Glasses", "images/effects/pink_glasses/icon.png") {

    pink_glasses_animation.setFPS(0);
    pink_glasses_animation.addFrame("images/effects/pink_glasses/pink_glasses.png");

}
EffectPinkGlasses::~EffectPinkGlasses() {}

void EffectPinkGlasses::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();

        // Calculate the position of animation
        int animation_width = face.width * 1.2;

        int left = face.tl().x - (animation_width - face.width) / 2;
        int bottom = face.tl().y + animation_width * 0.6;

        pink_glasses_animation.apply(draw, animation_width, left, bottom); 
    }

}

