
#include "animation.h"

using namespace cv;

Animation::Animation() {}
Animation::~Animation() {}

// Add a frame to animation
void Animation::addFrame(const std::string& img_path) {
    fs::path abs_img_path = fs::absolute(img_path);
    cv::Mat frame;
    frame = cv::imread(abs_img_path.string(), -1);
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

void Animation::overlayImage(const cv::Mat& background, const cv::Mat& foreground,
                  cv::Mat& output, cv::Point2i location) {
    background.copyTo(output);

    // start at the row indicated by location, or at row 0 if location.y is
    // negative.
    for (int y = std::max(location.y, 0); y < background.rows; ++y) {
        int fY = y - location.y;  // because of the translation

        // we are done of we have processed all rows of the foreground image.
        if (fY >= foreground.rows) break;

        // start at the column indicated by location,

        // or at column 0 if location.x is negative.
        for (int x = std::max(location.x, 0); x < background.cols; ++x) {
            int fX = x - location.x;  // because of the translation.

            // we are done with this row if the column is outside of the
            // foreground image.
            if (fX >= foreground.cols) break;

            // determine the opacity of the foregrond pixel, using its fourth
            // (alpha) channel.
            double opacity =
                ((double)foreground.data[fY * foreground.step +
                                         fX * foreground.channels() + 3])

                / 255.;

            // and now combine the background and foreground pixel, using the
            // opacity,

            // but only if opacity > 0.
            for (int c = 0; opacity > 0 && c < output.channels(); ++c) {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step +
                                    fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step +
                                    x * background.channels() + c];
                output.data[y * output.step + output.channels() * x + c] =
                    backgroundPx * (1. - opacity) + foregroundPx * opacity;
            }
        }
    }
}


cv::Mat Animation::rotateImage(const cv::Mat & img, double angle) {

    // Get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((img.cols-1) / 2.0, (img.rows-1) / 2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

    // Determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), img.size(), angle).boundingRect2f();

    // Adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - img.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - img.rows/2.0;

    cv::Mat dst;
    cv::warpAffine(img, dst, rot, bbox.size());
    return dst;
}

// Apply animation into image at position cv::Rect rect
void Animation::apply(cv::Mat& draw, int animation_width, int left,
                      int bottom, double angle)  {
    const cv::Mat& animation = getFrame();

    float scale_factor = static_cast<float>(animation_width) / animation.cols;

    // Optain the scaled animation
    cv::Mat scaled_animation;
    cv::resize(animation, scaled_animation, cv::Size(), scale_factor,
               scale_factor);

    // Rotate
    if (angle) {
        scaled_animation = rotateImage(scaled_animation, angle);
    }

    // overlayImage(draw, scaled_animation, left, bottom);
    cv::Mat result;
    int y1 = bottom - scaled_animation.rows;
    overlayImage(draw, scaled_animation, result, cv::Point2i(left, y1));
    draw = result;
}
