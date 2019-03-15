
#include "effect_feather_hat.h"

EffectFeatherHat::EffectFeatherHat()
    : ImageEffect("Feather Hat", "images/effects/feather_hat/icon.png") {

    feather_hat_animation.setFPS(0);
    feather_hat_animation.addFrame("images/effects/feather_hat/feather_hat.png");

}
EffectFeatherHat::~EffectFeatherHat() {}

void EffectFeatherHat::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();

        // Calculate the position of animation
        int animation_width = face.width * 3.2;

        int left = face.tl().x - (animation_width - face.width) / 2;
        int bottom = face.br().y + face.height / 10;

        feather_hat_animation.apply(draw, animation_width, left, bottom);
    }

}

