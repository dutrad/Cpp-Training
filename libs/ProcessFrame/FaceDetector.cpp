#include "FaceDetector.h"

FaceDetector::FaceDetector() {
    // Load the pre-trained Haar Cascade classifier for face detection
    if (!faceCascade.load("/media/beatriz/Dados/gitHub/Cpp-Training/haarcascade_frontalface_default.xml")) {
        throw std::runtime_error("Could not load Haar Cascade classifier");
    }
}

void FaceDetector::processFrame(cv::Mat& frame) {
    std::vector<cv::Rect> faces;
    // Convert the frame to grayscale for better detection
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    
    // Detect faces in the frame
    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3, 0, cv::Size(30, 30));

    // Draw rectangles around detected faces
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
    }
}