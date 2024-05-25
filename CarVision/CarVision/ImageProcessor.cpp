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
	cv::Size newSize(std::get<0>(resolutionMap[resolution]), std::get<1>(resolutionMap[resolution]));
	std::vector<cv::Rect> bodies;
	cv::cuda::GpuMat gpuImg, grayImg;

	// Resize the image to desired resolution
	cv::resize(img, img, newSize);

	// Upload image to GPU
	gpuImg.upload(img);

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
		cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(255, 0, 255), 2);
	}

	return img;
}
