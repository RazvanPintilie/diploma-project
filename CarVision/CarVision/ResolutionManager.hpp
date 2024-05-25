#pragma once
#include <map>
#include <tuple>

enum class ResolutionType { FHD, HD, SVGA };
using Resolution = std::tuple<int, int>;

class ResolutionManager
{
public:
    static std::map<ResolutionType, Resolution> CreateResolutionsMap();
};
