#pragma once

#include "IProcessFrame.h"

#include <opencv2/objdetect.hpp>

class ProcessFaceDetect : public IProcessFrame {
private:
  cv::CascadeClassifier faceCascade;

public:
  ProcessFaceDetect(const std::string &cascadePath);
  virtual void processFrame(cv::Mat &frame) override;
};
