
#include "effect_debug_info.h"

EffectDebugInfo::EffectDebugInfo()
    : ImageEffect("Debug Info", "images/effects/debug_info/icon.png") {}
EffectDebugInfo::~EffectDebugInfo() {}


void EffectDebugInfo::outputFPS(float detection_fps, float alignment_fps) {
    this->current_detection_fps = detection_fps;
    this->current_alignment_fps = alignment_fps;
}

void EffectDebugInfo::apply(cv::Mat& draw,
                            std::vector<LandMarkResult>& landmarks) {
    // Draw face bounding boxes and landmarks
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect r = landmarks[i].getFaceRect();
        cv::rectangle(draw, r, cv::Scalar(0, 255, 0), 2);
        ml_cam::setLabel(
            draw,
            std::string("confidence: ") +
                std::to_string(landmarks[i].getFaceRectConfidence()),
            r.tl());

        std::vector<cv::Point2f> landmark_points = landmarks[i].getFaceLandmark();
            if (!landmark_points.empty()) {
                for (unsigned long k = 0; k < landmark_points.size(); k++) {
                cv::circle(draw, landmark_points[k], 5, cv::Scalar(0, 0, 255), cv::FILLED);
            }
        }

    }

    // Frame size
    ml_cam::setLabel(draw, std::string("Frame Size: ") +
            std::to_string(draw.cols) + " x " + std::to_string(draw.rows), cv::Point(10, 25));


    // Calculate FPS
    if (Timer::calcTimePassed(last_calc_fps_time) > fps_valid_duration) {

        // Overall performance - FPS
        Timer::time_duration_t frame_duration = Timer::calcTimePassed(last_draw_time);
        displayed_overall_fps = 1000.0 / frame_duration;
        displayed_detection_fps = current_detection_fps;
        displayed_alignment_fps = current_alignment_fps;

        last_calc_fps_time = Timer::getCurrentTime();
    }

    // Output FPS
    ml_cam::setLabel(draw, std::string("Overall FPS: ") +
            std::to_string(displayed_overall_fps), cv::Point(10, 45));

    ml_cam::setLabel(draw, std::string("Face Detection FPS: ") +
            std::to_string(displayed_detection_fps == 0 ? -1 : displayed_detection_fps), cv::Point(10, 65));

    ml_cam::setLabel(draw, std::string("Face Alignment FPS: ") +
            std::to_string(displayed_alignment_fps == 0 ? -1 : displayed_alignment_fps), cv::Point(10, 85));

    
    last_draw_time = Timer::getCurrentTime();
            
}