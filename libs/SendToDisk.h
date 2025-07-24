#ifndef SENDTODISK_H
#define SENDTODISK_H

#include "ISendFrame.h"
#include <string>

class SendToDisk : public ISendFrame
{
private:
    int frameCount;
    std::string outputDir;

public:
    SendToDisk(const std::string &dir = "./frame");
    void sendFrame(cv::Mat &frame) override;
};

#endif