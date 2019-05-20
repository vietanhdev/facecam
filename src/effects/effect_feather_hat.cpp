
#include "effect_feather_hat.h"

EffectFeatherHat::EffectFeatherHat()
    : ImageEffect("Feather Hat", "images/effects/feather_hat/icon.png") {

    feather_hat_animation.setFPS(0);
    feather_hat_animation.addFrame("images/effects/feather_hat/feather_hat.png");

}
EffectFeatherHat::~EffectFeatherHat() {}

void EffectFeatherHat::apply(cv::Mat & draw, std::vector<LandMarkResult> & faces) {

    // *** Draw animation
    for (size_t i = 0; i < faces.size(); ++i) {

        // If we have landmark of face, use it to draw better
        if (faces[i].haveLandmark()) {

            std::vector<cv::Point2f> face_landmark = faces[i].getFaceLandmark();

            // Calculate the angle of glasses
            cv::Point left_point; // Left most point of left eye
            cv::Point right_point; // Right most point of right eye

            // If using 15 point landmark
            if (face_landmark.size() == 15) {
                left_point = face_landmark[5]; // Left most point of left eye
                right_point =  face_landmark[3]; // Right most point of right eye
            } else { // Using 64 point landmark
                left_point = face_landmark[36]; // Left most point of left eye
                right_point =  face_landmark[45]; // Right most point of right eye
            }
            
            double angle = - atan2(right_point.y - left_point.y, right_point.x - left_point.x) * 180 / 3.14;

            // Calculate the position of animation
            int eyes_width = std::abs(left_point.x - right_point.x);
            int animation_width = eyes_width * 4.5;

            int left = left_point.x - (animation_width - eyes_width) / 2;
            int bottom = std::max(left_point.y, right_point.y) + eyes_width * 1.2;

            feather_hat_animation.apply(draw, animation_width, left, bottom, angle); 

        } else {

            cv::Rect face = faces[i].getFaceRect();

            // Calculate the position of animation
            int animation_width = face.width * 3.2;

            int left = face.tl().x - (animation_width - face.width) / 2;
            int bottom = face.br().y + face.height / 10;

            feather_hat_animation.apply(draw, animation_width, left, bottom);

        }


    }

}

