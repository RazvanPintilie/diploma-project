#include "ImageProcessor.hpp"
#include <opencv2/opencv.hpp>

std::vector<cv::Mat> ImageProcessor::GetImagesFromFolder(const std::string& folderPath)
{
	std::vector<cv::String> imagePaths;
	std::vector<cv::Mat> images;

	cv::glob(folderPath + "*.jpg", imagePaths);

	if (imagePaths.empty())
	{
		std::cout << "No images found in folder: " << folderPath << std::endl;
	}

	for (const auto& imgPath : imagePaths)
	{
		cv::Mat img = cv::imread(imgPath);
		images.push_back(img);
	}

	return images;
}

cv::Mat ImageProcessor::ProcessImage(const cv::Mat& img, ResolutionType resolution)
{
	auto resolutionMap = ResolutionManager::CreateResolutionsMap();
	cv::Size newSize(resolutionMap[resolution]);
	std::vector<cv::Rect> bodies;
	cv::cuda::GpuMat gpuImg, grayImg;

	// Resize the image to desired resolution
	cv::Mat resizedImg;
	cv::resize(img, resizedImg, newSize);

	if (resizedImg.empty())
	{
		std::cout << "ERROR! Resized image is empty\n";
		return img;
	}

	// Upload image to GPU
	gpuImg.upload(resizedImg);

	// Convert image to grayscale on GPU
	cv::cuda::cvtColor(gpuImg, grayImg, cv::COLOR_BGR2GRAY);

	// HOG descriptor with default people detector
	cv::Ptr<cv::cuda::HOG> hog = cv::cuda::HOG::create();
	hog->setSVMDetector(hog->getDefaultPeopleDetector());

	// Detect people in the image
	hog->detectMultiScale(grayImg, bodies);

	// Download processed image back to CPU
	cv::Mat processedImg;
	grayImg.download(processedImg);

	// Draw rectangles around detected people
	for (const auto& rect : bodies)
	{
		cv::Scalar color(255, 0, 255);
		DrawRectangle(resizedImg, rect, color);
	}

	return resizedImg;
}

cv::Mat ImageProcessor::DrawRectangle(cv::Mat img, cv::Rect rect, cv::Scalar color)
{
	cv::rectangle(img, rect.tl(), rect.br(), color, 2);

	return img;
}