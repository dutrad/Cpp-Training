#pragma once

#include "IProcessFrame.h"

class Process2Gray : public IProcessFrame {
 public:
    virtual void processFrame(cv::Mat &frame) override;
};
