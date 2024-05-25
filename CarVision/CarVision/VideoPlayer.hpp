#pragma once
#include <opencv2/opencv.hpp>
#include "ImageProcessor.hpp"
#include "ResolutionManager.hpp"

class VideoPlayer
{
public:
    VideoPlayer(const std::string& videoPath, ResolutionType resolution, ImageProcessor imageProcessor);
    int PlayVideo();
private:
    std::string videoPath;
    ResolutionType resolution;
    ImageProcessor imageProcessor;
};
