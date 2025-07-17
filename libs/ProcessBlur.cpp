#include "ProcessBlur.h"
#include <iostream>
#include <opencv2/imgproc.hpp>

void ProcessBlur::processFrame(cv::Mat &frame)
{
    if (frame.empty())
    {
        std::cerr << "Error: Empty frame";
        return;
    }
    
    cv::blur(frame, frame, cv::Size(10,10));
}