#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

// Define the resolution types
enum ResolutionType { FHD, HD, SVGA };

// Define a type for resolution
using Resolution = std::tuple<int, int>;

std::map<ResolutionType, Resolution> CreateResolutionsMap();

std::vector<cv::Mat> GetImagesFromFolder(std::string folderPath);

cv::Mat ProcessImage(cv::Mat img, ResolutionType resolution);

int PlayVideo(const std::string videoPath, ResolutionType resolution);