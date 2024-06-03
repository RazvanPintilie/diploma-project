#include "../inc/ImageProcessor.hpp"
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <fstream>

std::vector<BBoxElement> ImageProcessor::RoboflowPredict(const cv::Mat& img)
{
	std::string imagePath = "resources/output/temp-img.jpg";
	std::string predictionOutput = "resources/output/predictions.json";
	cv::imwrite(imagePath, img);

	std::ofstream file;
	file.open("DeployRoboflowModel.ps1");

	std::string powershell = R"([System.Convert]::ToBase64String([System.IO.File]::ReadAllBytes(")" + imagePath + R"(")) | Out-File -Encoding ASCII -FilePath encoded_image.txt ; curl.exe -d @$PWD\encoded_image.txt "https://detect.roboflow.com/carvision-7imcs/2?api_key=waYDB2KU5ky1eK8Vid0O" | Out-File -Encoding ASCII -FilePath ")" + predictionOutput + R"(" ; Remove-Item encoded_image.txt)";

	file << powershell << std::endl;
	file.close();

	system("powershell -ExecutionPolicy Bypass -F DeployRoboflowModel.ps1");

	remove("DeployRoboflowModel.ps1");

	return ParsePredictions(predictionOutput);
}

std::vector<BBoxElement> ImageProcessor::ParsePredictions(const std::string& predictionOutput)
{
	std::vector<BBoxElement> predictions;

	JsonParser parser;
	parser.ParseJson(predictionOutput);
	predictions = parser.GetPredictions();

	return predictions;
}

std::vector<cv::Mat> ImageProcessor::GetImagesFromFolder(const std::string& folderPath)
{
	std::vector<cv::String> imagePaths;
	std::vector<cv::Mat> images;

	// List of extensions to search for
	std::vector<std::string> extensions = { "*.jpg", "*.jpeg", "*.png", "*.bmp", "*.tiff", "*.webp" };

	// Iterate over each extension and gather image paths
	for (const auto& ext : extensions)
	{
		std::vector<cv::String> tempPaths;
		cv::glob(folderPath + ext, tempPaths);
		imagePaths.insert(imagePaths.end(), tempPaths.begin(), tempPaths.end());
	}

	// Check if any images were found
	if (imagePaths.empty())
	{
		std::cout << "No images found in folder: " << folderPath << std::endl;
		return images; // Return an empty vector if no images were found
	}

	for (const auto& imgPath : imagePaths)
	{
		cv::Mat img = cv::imread(imgPath);
		images.push_back(img);
	}

	return images;
}

cv::Mat ImageProcessor::ProcessImage(const cv::Mat& img, ResolutionType resolution, bool process)
{
	/*static int i = 0;
	cv::imwrite("resources/output/img" + std::to_string(i++) + ".jpg", img);*/

	auto resolutionMap = ResolutionManager::CreateResolutionsMap();
	cv::Size newSize(resolutionMap[resolution]);
	std::vector<cv::Rect> bodies;
	cv::cuda::GpuMat gpuImg, grayImg;

	// Resize the image to desired resolution
	static cv::Mat resizedImg;
	if (process == true)
	{
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
		//cv::Ptr<cv::cuda::HOG> hog = cv::cuda::HOG::create();
		//hog->setSVMDetector(hog->getDefaultPeopleDetector());

		//// Detect people in the image
		//hog->detectMultiScale(grayImg, bodies);

		// Draw rectangles around detected people
		//for (const auto& rect : bodies)
		//{
		//	// b g r color
		//	cv::Scalar magenta(255, 0, 255);
		//	cv::Scalar yellow(0, 255, 255);
		//	cv::Scalar green(0, 255, 0);
		//	cv::Scalar red(0, 0, 255);

		//	auto color = yellow;


		//	DrawRectangle(resizedImg, rect, color);
		//}

		auto bBoxElements = RoboflowPredict(resizedImg);

		for (const auto& elem : bBoxElements)
		{
			// b g r color
			cv::Scalar magenta(255, 0, 255);
			cv::Scalar yellow(0, 255, 255);
			cv::Scalar green(0, 255, 0);
			cv::Scalar red(0, 0, 255);

			auto color = yellow;

			cv::Rect rect = cv::Rect(elem.x - elem.width / 2, elem.y - elem.height / 2, elem.width, elem.height);

			DrawRectangle(resizedImg, rect, color);
		}

		// Download processed image back to CPU
		cv::Mat processedImg;
		grayImg.download(processedImg);
	}

	return resizedImg;
}

cv::Mat ImageProcessor::DrawRectangle(cv::Mat img, cv::Rect rect, cv::Scalar color)
{
	cv::rectangle(img, rect.tl(), rect.br(), color, 2);

	return img;
}

//cv::Mat ImageProcessor::ProcessImage(const cv::Mat& img, ResolutionType resolution)
//{
//	auto resolutionMap = ResolutionManager::CreateResolutionsMap();
//	cv::Size newSize(resolutionMap[resolution]);
//	std::vector<cv::Rect> bodies;
//	cv::cuda::GpuMat gpuImg, grayImg;
//
//	// Resize the image to desired resolution
//	cv::Mat resizedImg;
//	cv::resize(img, resizedImg, newSize);
//
//	if (resizedImg.empty())
//	{
//		std::cout << "ERROR! Resized image is empty\n";
//		return img;
//	}
//
//	// Predict using the neural network
//	std::vector<float> prediction = neuralNetwork.Predict(resizedImg);
//
//	// Draw rectangles around detected people (example logic)
//	for (const auto& rect : bodies)
//	{
//		cv::Scalar color(255, 0, 255);
//		DrawRectangle(resizedImg, rect, color);
//	}
//
//	return resizedImg;
//}