
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
            std::vector<cv::Point2f> right_eye = faces[i].getRightEye();
            std::vector<cv::Point2f> left_eye = faces[i].getLeftEye();

            cv::Rect right_eye_bound = cv::boundingRect(right_eye);
            cv::Rect left_eye_bound = cv::boundingRect(left_eye);
            cv::Rect eyes_bound = right_eye_bound | left_eye_bound;


            // Calculate the angle of glasses
            cv::Point p1 = left_eye_bound.tl();
            cv::Point p2 = right_eye_bound.tl();
            double angle = - atan2(p1.y - p2.y, p1.x - p2.x) * 180 / 3.14;

            // Calculate the position of animation
            int animation_width = eyes_bound.width * 2;

            int left = eyes_bound.tl().x - (animation_width - eyes_bound.width) / 2;
            int bottom = eyes_bound.br().y + eyes_bound.height * 2;

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

