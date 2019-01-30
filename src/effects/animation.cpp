
#include "animation.h"

using namespace cv;

Animation::Animation() {}
Animation::~Animation() {}

// Add a frame to animation
void Animation::addFrame(const std::string& img_path) {
    cv::Mat frame;
    frame = cv::imread(img_path, cv::IMREAD_COLOR);
    frames.push_back(frame);
}

// Get frame by index
const cv::Mat& Animation::getFrame(size_t index) {
    if (frames.size() == 0 || index < 0 || index >= frames.size()) {
        return cv::Mat();
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
        animation_frame_duration = 1000.0 / fps;
    }
}

void Animation::alphaBlend(Mat& foreground, Mat& background, Mat& alpha,
                           Mat& outImage) {
    // Find number of pixels.
    int numberOfPixels =
        foreground.rows * foreground.cols * foreground.channels();

    // Get floating point pointers to the data matrices
    float* fptr = reinterpret_cast<float*>(foreground.data);
    float* bptr = reinterpret_cast<float*>(background.data);
    float* aptr = reinterpret_cast<float*>(alpha.data);
    float* outImagePtr = reinterpret_cast<float*>(outImage.data);

    // Loop over all pixesl ONCE
    for (int i = 0; i < numberOfPixels;
         i++, outImagePtr++, fptr++, aptr++, bptr++) {
        *outImagePtr = (*fptr) * (*aptr) + (*bptr) * (1 - *aptr);
    }
}