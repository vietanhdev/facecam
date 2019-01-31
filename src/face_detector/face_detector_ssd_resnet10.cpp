#include "face_detector_ssd_resnet10.h"

FaceDetectorSSDResNet10::FaceDetectorSSDResNet10() {
    setDetectorName("SSD ResNet10");
    face_model = cv::dnn::readNetFromTensorflow(TENSORFLOW_WEIGHT_FILE, TENSORFLOW_CONFIG_FILE);
}

FaceDetectorSSDResNet10::~FaceDetectorSSDResNet10() {
}


std::vector<LandMarkResult> FaceDetectorSSDResNet10::detect(const cv::Mat & img) {

    // Detection results;
    std::vector <LandMarkResult> landmark_results; 

    const float confidence_threshold = 0.7f;
    const cv::Scalar mean_val(104.0, 177.0, 123.0);

    // Detect face using loaded model
    std::vector<cv::Rect> faces;
    
    int frame_width = img.cols;
    int frame_height = img.rows;
    cv::Mat input_blob = cv::dnn::blobFromImage(img, 1.0, cv::Size(300, 300), mean_val, true, false);

    face_model.setInput(input_blob, "data");
    cv::Mat detection = face_model.forward("detection_out");

    cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    for(int i = 0; i < detectionMat.rows; i++)
    {
        float confidence = detectionMat.at<float>(i, 2);

        if(confidence > confidence_threshold)
        {
            int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame_width);
            int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame_height);
            int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame_width);
            int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame_height);

            LandMarkResult landmark;
            landmark.setFaceRect(cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)), confidence);
            landmark_results.push_back(landmark);

        }
    }

    return landmark_results;

}