#pragma once

#include <opencv2/core.hpp>

class IProcessFrame {
    public:
        virtual void processFrame(cv::Mat &frame) = 0;
};
