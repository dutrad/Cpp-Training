#include "ProcessFaceDetect.h"

#include <opencv2/imgproc.hpp>

ProcessFaceDetect::ProcessFaceDetect(const std::string &cascadePath) {
  if (!faceCascade.load(cascadePath)) {
    throw std::runtime_error("Could not load face cascade classifier");
  }
}

void ProcessFaceDetect::processFrame(cv::Mat &frame) {
  std::vector<cv::Rect> faces;
  faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0);

  for (const auto &face : faces) {
    cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
  }
}