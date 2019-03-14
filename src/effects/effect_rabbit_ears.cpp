
#include "effect_rabbit_ears.h"

EffectRabbitEars::EffectRabbitEars()
    : ImageEffect("Rabbit Ears", "images/effects/rabbit_ears/icon.png") {

    rabbit_ears_animation.setFPS(0);
    rabbit_ears_animation.addFrame("images/effects/rabbit_ears/rabbit_ears.png");

}
EffectRabbitEars::~EffectRabbitEars() {}

void EffectRabbitEars::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();
        rabbit_ears_animation.applyHat(draw, face);
    }

}

