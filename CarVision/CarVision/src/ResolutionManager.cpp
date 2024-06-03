#include "../inc/ResolutionManager.hpp"

std::map<ResolutionType, cv::Size> ResolutionManager::CreateResolutionsMap()
{
    std::map<ResolutionType, cv::Size> resolutionMap;

    resolutionMap[ResolutionType::FHD] = cv::Size(1920, 1080);
    resolutionMap[ResolutionType::HD] = cv::Size(1280, 720);
    resolutionMap[ResolutionType::nHD] = cv::Size(640, 360);
    resolutionMap[ResolutionType::SVGA] = cv::Size(800, 600);

    return resolutionMap;
}
