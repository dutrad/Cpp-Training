#pragma once

#include "IProcessFrame.h"

class ProcessBlur : public IProcessFrame {
 public:
    virtual void processFrame(cv::Mat &frame) override;
};
