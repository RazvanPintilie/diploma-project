#include "../inc/JsonParser.hpp"
#include <fstream>
#include <iostream>

void JsonParser::ParseJson(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file: " << filename << std::endl;
        return;
    }

    json jsonData;
    file >> jsonData;

    // Parse predictions from JSON
    for (const auto& prediction : jsonData["predictions"]) {
        BBoxElement bbox;
        bbox.x = prediction["x"];
        bbox.y = prediction["y"];
        bbox.width = prediction["width"];
        bbox.height = prediction["height"];
        bbox.confidence = prediction["confidence"];

        predictions.push_back(bbox);
    }
}
