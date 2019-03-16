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
    std::vector<int> considered_faces_idx; // Indices of faces we put into face_rects to find landmarks
    for (size_t i = 0; i < faces.size(); ++i) {
        
        cv::Rect face_rect = faces[i].getFaceRect();

        // Put face_rect into face_rects to find landmarks only if face_rect lies in the boundary of img.
        // This prevents crashing because of facemark->fit(img, face_rects, shapes);
        if ( 0 <= face_rect.x && 0 <= face_rect.width && face_rect.x + face_rect.width <= img.cols && 0 <= face_rect.y && 0 <= face_rect.height && face_rect.y + face_rect.height <= img.rows) {
            face_rects.push_back(face_rect);
            considered_faces_idx.push_back(i);
        }

    }

    // Detect face landmarks
    std::vector <std::vector<cv::Point2f>> shapes;
    facemark->fit(img, face_rects, shapes);


    // Merge detected landmarks to landmark results;
    for (size_t i = 0; i < considered_faces_idx.size(); ++i) {
        faces[considered_faces_idx[i]].setFaceLandmark(shapes[i]);
    }

    return faces;


}