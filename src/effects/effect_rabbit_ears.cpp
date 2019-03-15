
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

        // Calculate the position of animation
        int animation_width = face.width * 3;

        int left = face.tl().x - (animation_width - face.width) / 2;
        int bottom = face.tl().y + animation_width * 0.16;

        rabbit_ears_animation.apply(draw, animation_width, left, bottom); 
    }

}

