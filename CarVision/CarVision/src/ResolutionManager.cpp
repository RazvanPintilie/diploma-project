#include "../inc/ResolutionManager.hpp"

std::map<ResolutionType, cv::Size> ResolutionManager::CreateResolutionsMap()
{
    std::map<ResolutionType, cv::Size> resolutionMap;

    resolutionMap[ResolutionType::FHD] = cv::Size(1920, 1088);
    resolutionMap[ResolutionType::HD] = cv::Size(1280, 736);
    resolutionMap[ResolutionType::nHD] = cv::Size(640, 352);
    resolutionMap[ResolutionType::SVGA] = cv::Size(800, 608);

    return resolutionMap;
}
