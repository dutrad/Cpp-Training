#include "SendToDisk.h"
#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include <sstream>
#include <iomanip>

SendToDisk::SendToDisk(const std::string &dir) : frameCount(0), outputDir(dir) {
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directories(outputDir);
    }
}

void SendToDisk::sendFrame(cv::Mat &frame) {
    std::ostringstream filename;
    filename << outputDir << "/frame_" << std::setw(5) << std::setfill('0') << frameCount++ << ".png";
    
    if (!cv::imwrite(filename.str(), frame)) {
        throw std::runtime_error("Failed to save frame to disk: " + filename.str());
    }
}