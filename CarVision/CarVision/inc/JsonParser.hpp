#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp> // from https://github.com/nlohmann/json

// Define structures to hold image and annotation information
struct BBoxElement
{
	int x, y, width, height;
	float confidence;
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

class JsonParser
{
public:
	JsonParser(std::string filePath);
	void ParseJson(const std::string& filename);
	const std::vector<BBoxElement>& GetPredictions() const { return predictions; }

	// Function to load images and annotations from JSON file
	std::vector<std::pair<cv::Mat, std::vector<cv::Rect>>> loadDataFromJson(const std::string fileName);

private:
	using json = nlohmann::json;
	std::string filePath;
	std::vector<BBoxElement> predictions;
	std::vector<ImageElement> images;
	std::vector<AnnotationElement> annotations;
	void ParseCocoJson(const std::string& filename);
	const std::vector<ImageElement>& GetImages() const { return images; }
	const std::vector<AnnotationElement>& GetAnnotations() const { return annotations; }
	std::string GetImageFilePath(int imageId) const;

};
