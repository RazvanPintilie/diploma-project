#include "../inc/ResolutionManager.hpp"

std::map<ResolutionType, cv::Size> ResolutionManager::CreateResolutionsMap()
{
    std::map<ResolutionType, cv::Size> resolutionMap;

    resolutionMap[ResolutionType::FHD] = cv::Size(1920, 1080);
    resolutionMap[ResolutionType::HD] = cv::Size(1290, 720);
    resolutionMap[ResolutionType::SVGA] = cv::Size(800, 600);

    return resolutionMap;
}
