#pragma once
#include <map>
#include <tuple>
#include <opencv2/opencv.hpp>

enum class ResolutionType { FHD, HD, nHD, SVGA };

class ResolutionManager
{
public:
    static std::map<ResolutionType, cv::Size> CreateResolutionsMap();
};
