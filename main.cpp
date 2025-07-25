#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <filesystem>

#include "ProcessFaceDetect.h"
#include "Process2Gray.h"
#include "ProcessBlur.h"
#include "SendToDisk.h"
#include "SendToWindow.h"

int main(int argc, char **argv)
{
    cv::Mat frame;
    cv::VideoCapture cap;

    //IProcessFrame *process;
    //int processChoice = std::stoi(argv[1]);
    //if (processChoice == 0)
    //{
    //    process = new Process2Gray();
    //}
    //else {
    //    process = new ProcessBlur();
    //}

    std::vector<IProcessFrame*> processVec;
    processVec.push_back(new Process2Gray());
    //processVec.push_back(new ProcessBlur());
    processVec.push_back(new ProcessFaceDetect("../res/haarcascade_frontalface_default.xml"));

    std::vector<ISendFrame*> sendVec;
    sendVec.push_back(new SendToWindow());
    //sendVec.push_back(new SendToDisk("output_frames"));
    
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

        /*for (size_t i = 0; i < 2; i++)
        {
            processVec[i]->processFrame(frame);
        }
        
        cv::imshow("Live", frame);
        if (cv::waitKey(5) >= 0)
            break;*/
        for (auto& proc : processVec) {
            proc->processFrame(frame);
        }
        
        for (auto& sender : sendVec) {
            sender->sendFrame(frame);
        }

        if (cv::waitKey(5) >= 0)
            break;
            
    }

    for (auto& proc : processVec) {
        delete proc;
    }
    
    for (auto& sender : sendVec) {
        delete sender;
    }
    
    return 0;
}
