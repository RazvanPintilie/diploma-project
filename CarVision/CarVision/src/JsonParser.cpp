#include "../inc/JsonParser.hpp"
#include <fstream>
#include <iostream>

void JsonParser::ParseJson(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) 
	{
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

void JsonParser::ParseCocoJson(const std::string& filename)
{
	std::ifstream input(filename);
	if (!input.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	json j;
	input >> j;


	for (const auto& img : j["images"])
	{
		ImageElement image;
		image.id = img["id"];
		image.fileName = img["file_name"];
		image.height = img["height"];
		image.width = img["width"];
		images.push_back(image);
	}

	// Parse annotations from JSON
	for (const auto& ann : j["annotations"])
	{
		AnnotationElement annotation;
		annotation.imageId = ann["image_id"];
		annotation.categoryId = ann["category_id"];
		annotation.bbox.x = ann["bbox"][0];
		annotation.bbox.y = ann["bbox"][1];
		annotation.bbox.width = ann["bbox"][2];
		annotation.bbox.height = ann["bbox"][3];
		annotations.push_back(annotation);
	}
}

std::string JsonParser::GetImageFilePath(int imageId) const
{
	for (const auto& img : images)
	{
		if (img.id == imageId)
		{
			return img.fileName;
		}
	}
	return ""; // Return empty string if image ID is not found
}
