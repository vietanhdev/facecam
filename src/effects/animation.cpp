
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

// Apply animation into image at position cv::Rect rect
void Animation::apply(cv::Mat& draw, cv::Rect rect) {
    const cv::Mat& animation = getFrame();

    float scale_factor = static_cast<float>(rect.width) / animation.cols;

    // Optain the scaled animation
    cv::Mat scaled_animation;
    cv::resize(animation, scaled_animation, cv::Size(), scale_factor, scale_factor);

    // Calculate the position of animation
    int x1 = rect.tl().x;
    int y1 = rect.tl().y - rect.height / 5 - scaled_animation.rows;
    int x2 = x1 + scaled_animation.cols;
    int y2 = y1 + scaled_animation.rows;
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