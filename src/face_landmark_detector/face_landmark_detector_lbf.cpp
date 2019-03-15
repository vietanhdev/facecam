#include "face_landmark_detector_lbf.h"

FaceLandmarkDetectorLBF::FaceLandmarkDetectorLBF() {
    setDetectorName("LBF");
    fs::path MODEL_PATH_ABS = fs::absolute(MODEL_PATH);

    cv::face::FacemarkKazemi::Params params;
    facemark = cv::face::FacemarkLBF::create();


    facemark->loadModel(MODEL_PATH_ABS.string());
    
}

FaceLandmarkDetectorLBF::~FaceLandmarkDetectorLBF() {
}


std::vector<LandMarkResult> FaceLandmarkDetectorLBF::detect(const cv::Mat & img, std::vector<LandMarkResult> & faces) {

    if (faces.empty()) {
        return faces;
    }

    // Face face bounding boxes
    std::vector<cv::Rect> face_rects;
    for (size_t i = 0; i < faces.size(); ++i) {
        face_rects.push_back(faces[i].getFaceRect());
    }

    // Detect face landmarks
    std::vector <std::vector<cv::Point2f>> shapes;
    if(facemark->fit(img, face_rects, shapes));


    // Merge detected landmarks to landmark results;
    for (size_t i = 0; i < faces.size(); ++i) {
        faces[i].setFaceLandmark(shapes[i]);
    }

    return faces;


}