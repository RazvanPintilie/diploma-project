#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "functions.hpp"


int main()
{
	std::string videoPath = "resources/pedestrians/by_me_videos/tudor_pedestrians_rec_1_cut.mp4";
	std::string folderPath = "resources/pedestrians/by_me_images/";

	std::vector<cv::String> imagePaths;
	std::vector<cv::Mat> images = GetImagesFromFolder(folderPath);

	// Iterate over each image file path and read the image
	int index = 0;
	for (const auto& image : images)
	{
		std::string windowName = "Image " + std::to_string(++index);
		cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
		cv::Mat processedImage = ProcessImage(image, SVGA);

		cv::imshow(windowName, processedImage);
	}

	PlayVideo(videoPath, HD);

	cv::waitKey(0);
	return 0;
}