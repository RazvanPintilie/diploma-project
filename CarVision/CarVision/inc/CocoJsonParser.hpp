#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // from https://github.com/nlohmann/json

// Define structures to hold image and annotation information
struct BBoxElement
{
    int x, y, width, height;
};

struct AnnotationElement
{
    int imageId;
    int categoryId;
    BBoxElement bbox;
};

struct ImageElement
{
    int id;
    std::string fileName;
    int height;
    int width;
};

class CocoJsonParser 
{
public:
    CocoJsonParser() = default;

    void ParseJson(const std::string& filename);

    const std::vector<ImageElement>& GetImages() const { return images; }

    const std::vector<AnnotationElement>& GetAnnotations() const { return annotations; }

    std::string GetImageFilePath(int imageId) const;

private:
    std::vector<ImageElement> images;
    std::vector<AnnotationElement> annotations;

    using json = nlohmann::json;
};


