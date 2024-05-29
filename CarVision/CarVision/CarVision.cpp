#include "VideoPlayer.hpp"
#include "ImageProcessor.hpp"

int main()
{
	// cv::cuda::printCudaDeviceInfo(0);

	std::string videoPath;
	std::string iamgesFolderPath = "resources/dataset/images/test/";
	// iamgesFolderPath = "resourceS/temp/";
	videoPath = "resources/videos/tudor_pedestrians_rec_1_cut.mp4";
	// videoPath = "http://192.168.1.100:8080/video"; // Replace with smartphone's IP camera URL
	// videoPath = "http://192.168.159.107:8080/video"; // Replace with smartphone's IP camera URL

	int numEpochs = 10; // Define the number of epochs
	float learningRate = 0.001f; // Define the learning rate
	int batchSize = 32; // Define the batch size

	NeuralNetwork neuralNetwork(numEpochs, learningRate, batchSize);
	ImageProcessor imageProcessor(neuralNetwork);

	//std::vector<cv::Mat> images = imageProcessor.GetImagesFromFolder(iamgesFolderPath);
	//int index = 0;
	//for (const auto& image : images)
	//{
	//	std::string windowName = "Image " + std::to_string(++index);

	//	cv::Mat processedImage = imageProcessor.ProcessImage(image, ResolutionType::SVGA);

	//	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	//	cv::imshow(windowName, processedImage);
	//}

	VideoPlayer videoPlayer(videoPath, ResolutionType::HD, imageProcessor);
	videoPlayer.PlayVideo();

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}
