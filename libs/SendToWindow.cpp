#include "SendToWindow.h"
#include <opencv2/highgui.hpp>

void SendToWindow::sendFrame(cv::Mat &frame) {
    cv::imshow("Frame", frame);
}