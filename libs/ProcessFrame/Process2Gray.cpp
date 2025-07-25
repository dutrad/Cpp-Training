#include "IProcessFrame.h"
#include "Process2Gray.h"
#include <iostream>
#include <opencv2/imgproc.hpp>

void Process2Gray::processFrame(cv::Mat &frame)
{
    if (frame.empty())
    {
        std::cerr << "Error: Empty frame";
        return;
    }
    
    cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
}