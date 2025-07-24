#ifndef SENDTOWWINDOW_H
#define SENDTOWWINDOW_H

#include "ISendFrame.h"

class SendToWindow : public ISendFrame
{
public:
    void sendFrame(const cv::Mat &frame) override;
};

#endif // SENDTOWWINDOW_H
