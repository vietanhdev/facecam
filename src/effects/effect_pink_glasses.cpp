
#include "effect_pink_glasses.h"

EffectPinkGlasses::EffectPinkGlasses()
    : ImageEffect("Pink Glasses", "images/effects/pink_glasses/icon.png") {

    pink_glasses_animation.setFPS(0);
    pink_glasses_animation.addFrame("images/effects/pink_glasses/pink_glasses.png");

}
EffectPinkGlasses::~EffectPinkGlasses() {}

void EffectPinkGlasses::apply(cv::Mat & draw, std::vector<LandMarkResult> & faces) {

    // *** Draw cloud animation
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
            int animation_width = eyes_width * 1.6;

            int left = left_point.x - (animation_width - eyes_width) / 2;
            int bottom = std::max(left_point.y, right_point.y) + eyes_width * 0.35;

            pink_glasses_animation.apply(draw, animation_width, left, bottom, angle); 

            
        } else { // Otherwise, use only face bounding box

            cv::Rect face = faces[i].getFaceRect();

            // Calculate the position of animation
            int animation_width = face.width * 1.2;

            int left = face.tl().x - (animation_width - face.width) / 2;
            int bottom = face.tl().y + animation_width * 0.6;

            pink_glasses_animation.apply(draw, animation_width, left, bottom); 
        }

    }

}

