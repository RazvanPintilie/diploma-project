#include "ResolutionManager.hpp"

std::map<ResolutionType, Resolution> ResolutionManager::CreateResolutionsMap() 
{
    std::map<ResolutionType, Resolution> resolutionMap;

    resolutionMap[ResolutionType::FHD] = std::make_tuple(1920, 1080);
    resolutionMap[ResolutionType::HD] = std::make_tuple(1280, 720);
    resolutionMap[ResolutionType::SVGA] = std::make_tuple(800, 600);

    return resolutionMap;
}
