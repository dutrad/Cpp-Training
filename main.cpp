#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <filesystem>
#include <thread>
#include <queue>

#include "ProcessFaceDetect.h"
#include "Process2Gray.h"
#include "ProcessBlur.h"
#include "SendToDisk.h"
#include "SendToWindow.h"

std::queue<cv::Mat> toProcessQueue;
std::queue<cv::Mat> toSaveQueue;

std::mutex toProcessMutex;
std::mutex toSaveMutex;
std::atomic_bool finishedCapturing(false);
std::atomic_bool finishedProcessing(false);

void captureFrames(cv::VideoCapture &cap)
{
    cv::Mat frame;
    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            finishedCapturing = true;
            break;
        }
        {
            std::lock_guard<std::mutex> lock(toProcessMutex);
            toProcessQueue.push(frame.clone());
        }
        std::this_thread::yield();
    }
    std::cout << "Capture frames thread finished" << std::endl;
}

void processFrames(std::vector<IProcessFrame*> &processVec)
{
    while (true) {
        cv::Mat frame;
        {
            std::lock_guard<std::mutex> lock(toProcessMutex);
            if (toProcessQueue.empty()) {
                continue;
            }
            frame = toProcessQueue.front();
            toProcessQueue.pop();
        }

        for (auto& proc : processVec) {
            proc->processFrame(frame);
        }

        {
            std::lock_guard<std::mutex> lock(toSaveMutex);
            toSaveQueue.push(frame.clone());
        }

        if(finishedCapturing && toProcessQueue.empty()) {
            finishedProcessing = true;
            break;
        }
        std::this_thread::yield();
    }
    std::cout << "Process frames thread finished" << std::endl;
}

void sendFrames(std::vector<ISendFrame*> &sendVec)
{
    while (true) {
        cv::Mat frame;
        {
            std::lock_guard<std::mutex> lock(toSaveMutex);
            if (toSaveQueue.empty()) {
                continue;
            }
            frame = toSaveQueue.front();
            toSaveQueue.pop();
        }

        for (auto& sender : sendVec) {
            sender->sendFrame(frame);
        }
        if(finishedProcessing && toSaveQueue.empty()) break;
        std::this_thread::yield();
    }
    std::cout << "Save frames thread finished" << std::endl;
}

void processMultiThreads(cv::VideoCapture &cap, std::vector<IProcessFrame*> &processVec, std::vector<ISendFrame*> &sendVec)
{
    std::thread captureThread(captureFrames, std::ref(cap));
    std::thread processThread(processFrames, std::ref(processVec));
    std::thread sendThread(sendFrames, std::ref(sendVec));

    captureThread.join();
    processThread.join();
    sendThread.join();
}

void processSingleThread(cv::VideoCapture &cap, std::vector<IProcessFrame*> &processVec, std::vector<ISendFrame*> &sendVec)
{
    cv::Mat frame;
    while (true) {
        cap.read(frame);
        if (frame.empty()) break;

        for (auto& proc : processVec) {
            proc->processFrame(frame);
        }

        for (auto& sender : sendVec) {
            sender->sendFrame(frame);
        }
    }
}

int main(int argc, char **argv)
{
    cv::Mat frame;
    cv::VideoCapture cap;


    std::vector<IProcessFrame*> processVec;
    processVec.push_back(new Process2Gray());
    //processVec.push_back(new ProcessBlur());
    //processVec.push_back(new ProcessFaceDetect("../res/haarcascade_frontalface_default.xml"));

    std::vector<ISendFrame*> sendVec;
    //sendVec.push_back(new SendToWindow());
    sendVec.push_back(new SendToDisk("output_frames"));
    
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open("../input_frames/frame_%05d.png", apiID);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
 
    std::cout << "Start grabbing" << std::endl
        << "Press any key to terminate" << std::endl;

    auto now = std::chrono::system_clock::now();

    //processMultiThreads(cap, processVec, sendVec);
    processSingleThread(cap, processVec, sendVec);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
    std::cout << "Processing time: " << duration.count() << " milliseconds" << std::endl;

    for (auto& proc : processVec) {
        delete proc;
    }
    
    for (auto& sender : sendVec) {
        delete sender;
    }
    
    return 0;
}
