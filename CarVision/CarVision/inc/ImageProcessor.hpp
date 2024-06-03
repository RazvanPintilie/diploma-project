#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include "ResolutionManager.hpp"
#include "../inc/JsonParser.hpp"

class ImageProcessor
{
public:
	std::vector<BBoxElement> RoboflowPredict(const cv::Mat& img);
	cv::Mat ProcessImage(const cv::Mat& img, ResolutionType resolution, bool process);
	std::vector<cv::Mat> GetImagesFromFolder(const std::string& folderPath);

private:
	cv::Mat DrawRectangle(cv::Mat img, cv::Rect rect, cv::Scalar color);
	std::vector<BBoxElement> ParsePredictions(const std::string& predictionOutput);
};
