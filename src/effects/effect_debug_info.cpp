
#include "effect_debug_info.h"

EffectDebugInfo::EffectDebugInfo()
    : ImageEffect("Debug Info", "images/effects/debug_info/icon.png") {}
EffectDebugInfo::~EffectDebugInfo() {}

void EffectDebugInfo::apply(cv::Mat & draw, std::vector<LandMarkResult> & landmarks) {

    // Draw face bounding boxes
    for (size_t i = 0; i < landmarks.size(); ++i) {
        cv::Rect r = landmarks[i].getFaceRect();
        cv::rectangle(draw, r, cv::Scalar(0, 255, 0), 2);
        ml_cam::setLabel(draw, std::string("confidence: ") +
                        std::to_string(landmarks[i].getFaceRectConfidence()), r.tl());
    }

}