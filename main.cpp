#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
 
    std::cout << "Start grabbing" << std::endl
        << "Press any key to terminate" << std::endl;
    while(true) {
        cap.read(frame);

        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);

        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }
    return 0;
}
