#include "face_landmark_detector_syan_cnn_2.h"
#include <type_traits>

FaceLandmarkDetectorSyanCNN2::FaceLandmarkDetectorSyanCNN2() {
    setDetectorName("SyanCNN 2");
<<<<<<< HEAD
    fs::path MODEL_PATH_ABS = fs::absolute(MODEL_PATH);
=======
    fs::path TENSORFLOW_WEIGHT_FILE_PATH_ABS = fs::absolute(TENSORFLOW_WEIGHT_FILE);
    fs::path TENSORFLOW_CONFIG_FILE_PATH_ABS = fs::absolute(TENSORFLOW_CONFIG_FILE);
    face_model = cv::dnn::readNetFromTensorflow(TENSORFLOW_WEIGHT_FILE_PATH_ABS.string());
>>>>>>> master
}

FaceLandmarkDetectorSyanCNN2::~FaceLandmarkDetectorSyanCNN2() {}

std::vector<int> FaceLandmarkDetectorSyanCNN2::getFacialPoints(const cv::Mat & image) {
    std::vector<float> flat;

    for (int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            auto x = image.at<uchar>(i, j);
            flat.push_back(x/255);
        }
    }
<<<<<<< HEAD
=======

    face_model.setInput(flat);
    cv::Mat detection = face_model.forward();


    for (int i = 0; i < detection.rows; i++){
        for (int j = 0; j < detection.cols; j++){
            auto x = detection.at<uchar>(i, j);
            std::cout << detection.at<int>(i, j) << " ";
        }
    }
    std::cout << std::endl;

>>>>>>> master
    std::vector<int> facial_points;

    for (int i=0; i < detection.cols; i++){
        auto x = detection.at<uchar>(0, i);
        int xx = 48*x + 48;
        facial_points.push_back(xx);
    }

    return facial_points;
}

std::vector<LandMarkResult> FaceLandmarkDetectorSyanCNN2::detect(const cv::Mat & img, std::vector<LandMarkResult> & faces) {

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

    // Fit landmarks
    for (int i = 0; i < face_rects.size(); ++i) {

        std::vector<cv::Point2f> face_points;
        cv::Mat crop = img(face_rects[i]);
        cv::Mat gray_crop;
        cv::cvtColor(crop, gray_crop, cv::COLOR_BGR2GRAY);

        float fx = 96.0 / gray_crop.cols;
        float fy = 96.0 / gray_crop.rows;
        cv::resize(gray_crop, gray_crop, cv::Size(96, 96)); // The input image must be 96*96

        std::vector<int> facial_points = getFacialPoints(gray_crop);

        int num_points = facial_points.size()/2;
        for(int j = 0; j < num_points; j++){
            float x = facial_points[j*2] / fx + face_rects[i].x;
            float y = facial_points[j*2+1] / fy + face_rects[i].y;
            cv::Point p = cv::Point(x, y);
            face_points.push_back(p);
        }

        shapes.push_back(face_points);

    }

    // Merge detected landmarks to landmark results;
    for (size_t i = 0; i < considered_faces_idx.size(); ++i) {
        faces[considered_faces_idx[i]].setFaceLandmark(shapes[i]);
    }

    return faces;


}