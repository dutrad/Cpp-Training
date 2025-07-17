#pragma once

#include <opencv2/core.hpp>

class ISendFrame {
    public:
        virtual void sendFrame(cv::Mat &frame) = 0;
};
