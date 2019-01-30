
#include "effect_cloud.h"

EffectCloud::EffectCloud()
    : ImageEffect("Raining Cloud", "../images/effects/cloud/icon.png") {

    cloud_animation.setFPS(5);
    cloud_animation.addFrame("../images/effects/cloud/cloud_animation_1/1.png");
    cloud_animation.addFrame("../images/effects/cloud/cloud_animation_1/2.png");
    cloud_animation.addFrame("../images/effects/cloud/cloud_animation_1/3.png");

}
EffectCloud::~EffectCloud() {}

void EffectCloud::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // *** Draw cloud animation
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect face = landmarks[i].getFaceRect();
        const cv::Mat & cloud_img = cloud_animation.getFrame().clone();
        
        float scale_factor = static_cast<float>(face.width) / cloud_img.cols;

        // Optain the scaled cloud
        cv::Mat scaled_cloud;
        cv::resize(cloud_img, scaled_cloud, cv::Size(), scale_factor, scale_factor);

        // Calculate the position of cloud
        int x1 = face.tl().x;
        int y1 = face.tl().y - face.height / 5 - scaled_cloud.rows;
        int x2 = x1 + scaled_cloud.cols;
        int y2 = y1 + scaled_cloud.rows;
        cv::Point tl(x1, y1);
        cv::Point br(x2, y2);
        cv::Rect cloud_position(tl, br);

        if (x1 < 0 || y1 < 0 || x2 >= draw.cols || y2 >= draw.rows) {
            continue;
        }

        // Merge clouds into image
        cv::Mat roi = draw(cloud_position); // Image of background image
        cv::Mat mask;
        cv::Mat mask_inv;
        cv::Mat scaled_cloud_gray; cv::cvtColor(scaled_cloud, scaled_cloud_gray, cv::COLOR_BGR2GRAY);
        cv::threshold(scaled_cloud_gray, mask, 1, 255, cv::THRESH_BINARY);
        cv::bitwise_not(mask, mask_inv);

        cv::Mat background, foreground;
        cv::bitwise_and(roi, roi, background, mask_inv);
        cv::bitwise_and(scaled_cloud, scaled_cloud, foreground, mask);
        
        cv::Mat merged;
        cv::add(background, foreground, merged);
        
        merged.copyTo(roi);

    }

}