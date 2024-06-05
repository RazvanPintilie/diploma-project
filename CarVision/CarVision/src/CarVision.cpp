#include <torch/torch.h>
#include "../inc/VideoPlayer.hpp"

int main()
{
	// cv::cuda::printCudaDeviceInfo(0);

	//at::Tensor a = at::ones({ 2, 2 }, at::kInt);
	//at::Tensor b = at::randn({ 2, 2 });
	//auto c = a + b.to(at::kInt);

	std::string videoPath;
	std::string iamgesFolderPath = "resources/images/test/";
	// iamgesFolderPath = "resourceS/temp/";
	videoPath = "resources/videos/tudor_pedestrians_rec_1_cut.mp4";
	// videoPath = "http://192.168.53.188:8080/video"; // Replace with smartphone's IP camera URL
	// videoPath = "http://192.168.1.101:8080/video"; // Replace with smartphone's IP camera URL

	ImageProcessor imageProcessor;

	/*std::vector<cv::Mat> images = imageProcessor.GetImagesFromFolder(iamgesFolderPath);
	int index = 0;
	for (const auto& image : images)
	{
		std::string windowName = "Image " + std::to_string(++index);

		cv::Mat processedImage = imageProcessor.ProcessImage(image, ResolutionType::SVGA, true);

		 cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
		 cv::imshow(windowName, processedImage);
	}*/

	VideoPlayer videoPlayer(videoPath, ResolutionType::HD, imageProcessor);
	videoPlayer.PlayVideo();


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create an instance of the CocoJsonParser class
	// JsonParser parser;
	// parser.ParseCocoJson("resources/dataset/train/_annotations.coco.json");
	   
	// // Get parsed images and annotations
	// const auto& images = parser.GetImages();
	// const auto& annotations = parser.GetAnnotations();
	   
	// // Example: Print parsed data
	// std::cout << "Parsed " << images.size() << " images and " << annotations.size() << " annotations.\n";
	   
	// // Iterate over images and annotations
	// for (const auto& image : images)
	// {
	// 	std::cout << "Image ID: " << image.id << ", File: " << image.fileName << ", Size: " << image.width << "x" << image.height << std::endl;
	// }
	   
	// for (const auto& annotation : annotations)
	// {
	// 	std::cout << "Annotation - Image ID: " << annotation.imageId << ", Category ID: " << annotation.categoryId
	// 		<< ", BBox: [" << annotation.bbox.x << ", " << annotation.bbox.y << ", " << annotation.bbox.width << ", " << annotation.bbox.height << "]\n";
	// }


	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}

