
#include "animation.h"

using namespace cv;

Animation::Animation() {}
Animation::~Animation() {}

// Add a frame to animation
void Animation::addFrame(const std::string& img_path) {
	fs::path abs_img_path = fs::absolute(img_path);
    cv::Mat frame;
    frame = cv::imread(abs_img_path.string(), cv::IMREAD_COLOR);
    frames.push_back(frame);
}

// Get frame by index
const cv::Mat& Animation::getFrame(size_t index) {
    if (frames.size() == 0 || index < 0 || index >= frames.size()) {
        return dummy_frame;
    } else {
        return frames[index];
    }
}

// Get current frame
const cv::Mat& Animation::getFrame() {
    // *** Calculate current frame index

    Timer::time_duration_t duration_from_last_ani =
        Timer::calcTimePassed(last_animation_time);

    // If current frame is old enough, replace it with the new frame
    if (duration_from_last_ani > animation_frame_duration) {
        current_frame_index += 1;
        current_frame_index = current_frame_index % frames.size();
        last_animation_time = Timer::getCurrentTime();
    }

    // *** return frame
    return getFrame(current_frame_index);
}

// Set fps of animation
void Animation::setFPS(float fps) {
    if (fps > 0) {
        animation_frame_duration = static_cast<long int>(1000.0 / fps);
    }
}


// Overlay image to another image
void Animation::overlayImage(cv::Mat & draw, cv::Mat & overlay, int x, int bottom_y) {
   
    // Calculate the position of overlay
    int y2 = bottom_y;
    int x1 = x;
    int y1 = y2 - overlay.rows;
    int x2 = x1 + overlay.cols;
    
    cv::Rect overlay_crop_window(0, 0, overlay.cols, overlay.rows);
    std::cout << overlay_crop_window << std::endl;

    // The left edge of overlay goes over the image boundary
    if (x1 < 0) {
        int x_increment = -x1;
        overlay_crop_window.x += x_increment;
        overlay_crop_window.width -= x_increment;
        x1 = 0;
    }

    // The top edge of overlay goes over the image boundary
    if (y1 < 0) {
        int y_increment = -y1;
        overlay_crop_window.y += y_increment;
        overlay_crop_window.height -= y_increment;
        y1 = 0;
    }

    // The right edge of overlay goes over the image boundary
    if (x2 >= draw.cols) {
        overlay_crop_window.width -= x2 - draw.cols + 1;
        x2 = draw.cols - 1;
    }

    // The bottom edge of overlay goes over the image boundary
    if (y2 >= draw.rows) {
        overlay_crop_window.height -= y2 - draw.rows + 1;
        y2 = draw.rows - 1;
    }

    cv::Point tl(x1, y1);
    cv::Point br(x2, y2);
    cv::Rect overlay_pos(tl, br);

    std::cout << overlay_crop_window << std::endl;

    cv::Mat crop_overlay = overlay(overlay_crop_window);

    // Merge overlay into image
    cv::Mat roi = draw(overlay_pos);  // Image of background image
    cv::Mat mask;
    cv::Mat mask_inv;
    cv::Mat crop_overlay_gray;
    cv::cvtColor(crop_overlay, crop_overlay_gray, cv::COLOR_BGR2GRAY);
    cv::threshold(crop_overlay_gray, mask, 1, 255, cv::THRESH_BINARY);
    cv::bitwise_not(mask, mask_inv);

    cv::Mat background, foreground;
    cv::bitwise_and(roi, roi, background, mask_inv);
    cv::bitwise_and(crop_overlay, crop_overlay, foreground, mask);

    cv::Mat merged;
    cv::add(background, foreground, merged);

    merged.copyTo(roi);

}

// Apply animation into image at position cv::Rect rect
void Animation::apply(cv::Mat& draw, cv::Rect rect) {
    const cv::Mat& animation = getFrame();

    float scale_factor = static_cast<float>(rect.width) / animation.cols;

    // Optain the scaled animation
    cv::Mat scaled_animation;
    cv::resize(animation, scaled_animation, cv::Size(), scale_factor, scale_factor);

    // Calculate the position of animation
    int x = rect.tl().x;
    int bottom_y = rect.tl().y - rect.height / 5;

    overlayImage(draw, scaled_animation, x, bottom_y);
    
}


// Apply animation into image at position cv::Rect rect
void Animation::applyHat(cv::Mat& draw, cv::Rect rect) {
    const cv::Mat& animation = getFrame();

    float scale_factor = static_cast<float>(rect.width) / animation.cols * 1.5;

    // Optain the scaled animation
    cv::Mat scaled_animation;
    cv::resize(animation, scaled_animation, cv::Size(), scale_factor, scale_factor);

    // Calculate the position of animation
    int x1 = rect.tl().x - scaled_animation.cols * 0.2;
    int y2 = rect.tl().y - rect.height * 0.1;
    int x2 = x1 + scaled_animation.cols;
    int y1 = y2 - scaled_animation.rows;
    cv::Point tl(x1, y1);
    cv::Point br(x2, y2);
    cv::Rect animation_pos(tl, br);

    if (x1 < 0 || y1 < 0 || x2 >= draw.cols || y2 >= draw.rows) {
        return;
    }

    // Merge animation into image
    cv::Mat roi = draw(animation_pos);  // Image of background image
    cv::Mat mask;
    cv::Mat mask_inv;
    cv::Mat scaled_animation_gray;
    cv::cvtColor(scaled_animation, scaled_animation_gray, cv::COLOR_BGR2GRAY);
    cv::threshold(scaled_animation_gray, mask, 1, 255, cv::THRESH_BINARY);
    cv::bitwise_not(mask, mask_inv);

    cv::Mat background, foreground;
    cv::bitwise_and(roi, roi, background, mask_inv);
    cv::bitwise_and(scaled_animation, scaled_animation, foreground, mask);

    cv::Mat merged;
    cv::add(background, foreground, merged);

    merged.copyTo(roi);
}