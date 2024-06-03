#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // from https://github.com/nlohmann/json

// Define structures to hold image and annotation information
struct BBoxElement
{
    int x, y, width, height;
    float confidence;
};

class JsonParser
{
public:
    JsonParser() = default;

    void ParseJson(const std::string& filename);

    const std::vector<BBoxElement>& GetPredictions() const { return predictions; }

private:
    std::vector<BBoxElement> predictions;

    using json = nlohmann::json;
};
