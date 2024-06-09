#include "../inc/JsonParser.hpp"
#include <fstream>
#include <iostream>

JsonParser::JsonParser(std::string filePath)
{
	this->filePath = filePath;
}

std::vector<std::pair<cv::Mat, std::vector<cv::Rect>>> JsonParser::loadDataFromJson(const std::string fileName)
{
	std::vector<std::pair<cv::Mat, std::vector<cv::Rect>>> result;

	// Load JSON file and parse annotations
	ParseCocoJson(this->filePath + fileName);

	// Get parsed images and annotations
	const auto& images = GetImages();
	const auto& annotations = GetAnnotations();

	// Map to store image file paths with corresponding bounding boxes
	std::map<int, std::vector<cv::Rect>> imageIdToBBoxesMap;

	for (const auto& annotation : annotations)
	{
		// std::cout << "Annotation - Image ID: " << annotation.imageId << ", Category ID: " << annotation.categoryId
		//	<< ", BBox: [" << annotation.bbox.x << ", " << annotation.bbox.y << ", " << annotation.bbox.width << ", " << annotation.bbox.height << "]\n";

		cv::Rect rect = cv::Rect(annotation.bbox.x, annotation.bbox.y, annotation.bbox.width, annotation.bbox.height);
		imageIdToBBoxesMap[annotation.imageId].push_back(rect);
	}

	// Iterate through images and load them with their bounding boxes
	for (const auto& image : images)
	{
		std::string imagePath = GetImageFilePath(image.id);
		if (!imagePath.empty())
		{
			cv::Mat img = cv::imread(imagePath);
			if (!img.empty())
			{
				result.emplace_back(img, imageIdToBBoxesMap[image.id]);
			}
			else
			{
				std::cerr << "Error loading image: " << imagePath << std::endl;
			}
		}
	}
	   
	// test the output
	// for (const auto& r : result)
	// {
	// 	for (const auto& rect : r.second)
	// 	{
	// 		cv::Scalar color(0, 255, 255);
	// 		cv::rectangle(r.first, rect.tl(), rect.br(), color, 2);
	   
	// 		cv::waitKey(0);
	// 	}
	// 	cv::imshow("ok", r.first);
	// }

	return result;
}

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
			return this->filePath + img.fileName;
		}
	}
	return ""; // Return empty string if image ID is not found
}
