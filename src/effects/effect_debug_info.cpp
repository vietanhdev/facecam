
#include "effect_debug_info.h"

EffectDebugInfo::EffectDebugInfo()
    : ImageEffect("Debug Info", "images/effects/debug_info/icon.png") {}
EffectDebugInfo::~EffectDebugInfo() {}

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
        for (unsigned long k = 0; k < landmark_points.size(); k++) {
            cv::circle(draw, landmark_points[k], 5, cv::Scalar(0, 0, 255), cv::FILLED);
        }

        cv::circle(draw, landmark_points[45], 5, cv::Scalar(0, 255, 0), cv::FILLED); // Right most point of right eye
        cv::circle(draw, landmark_points[36], 5, cv::Scalar(0, 255, 0), cv::FILLED); // Left most point of left eye
    }

    // Frame info
    cv::putText(draw, std::string("Frame Size: ") +
            std::to_string(draw.cols) + " x " + std::to_string(draw.rows), cv::Point(10, 25), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0), 1);

            
}