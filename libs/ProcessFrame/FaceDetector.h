#pragma once
#include <opencv2/opencv.hpp>
#include "IProcessFrame.h"

class FaceDetector : public IProcessFrame {
public:
    FaceDetector();
    void processFrame(cv::Mat& frame) override;

private:
    cv::CascadeClassifier faceCascade;
};
