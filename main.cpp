#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <stdio.h>

int main()
{
    cv::Mat frame;
    cv::VideoCapture cap;
    cv::CascadeClassifier face_cascade;

    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);

    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
        
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "ERROR! Unable to load face cascade\n";
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
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(frame, faces, 1.1, 3, 0);

        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
        }

        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;
    }
    return 0;
}
