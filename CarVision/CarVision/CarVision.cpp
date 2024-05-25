#include "VideoPlayer.hpp"
#include "ImageProcessor.hpp"

int main()
{
	std::string videoPath = "resources/pedestrians/by_me_videos/tudor_pedestrians_rec_1_cut.mp4";
	// std::string videoPath = "http://192.168.1.101:8080/video"; // Replace with smartphone's IP camera URL
	// std::string videoPath = "http://192.168.159.107:8080/video"; // Replace with smartphone's IP camera URL
	std::string iamgesFolderPath = "resources/pedestrians/by_me_images/";

	ImageProcessor imageProcessor;
	std::vector<cv::Mat> images = imageProcessor.GetImagesFromFolder(iamgesFolderPath);

	/*int index = 0;
	for (const auto& image : images)
	{
		std::string windowName = "Image " + std::to_string(++index);
		cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

		cv::Mat processedImage = imageProcessor.ProcessImage(image, ResolutionType::SVGA);

		cv::imshow(windowName, processedImage);
	}*/

	VideoPlayer videoPlayer(videoPath, ResolutionType::HD, imageProcessor);
	videoPlayer.PlayVideo();

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}
