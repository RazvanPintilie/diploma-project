// #include <torch/torch.h>
// #include "../inc/VideoPlayer.hpp"
// 
// int main()
// {
// 	// cv::cuda::printCudaDeviceInfo(0);
// 
// 	// at::Tensor a = at::ones({ 2, 2 }, at::kInt);
// 	// at::Tensor b = at::randn({ 2, 2 });
// 	// auto c = a + b.to(at::kInt);
// 
// 	std::string videoPath;
// 	std::string iamgesFolderPath = "resources/images/test/";
// 	// iamgesFolderPath = "resourceS/temp/";
// 	videoPath = "resources/videos/tudor_pedestrians_rec_1_cut.mp4";
// 	// videoPath = "http://192.168.53.188:8080/video"; // Replace with smartphone's IP camera URL
// 	// videoPath = "http://192.168.1.101:8080/video"; // Replace with smartphone's IP camera URL
// 
// 	ImageProcessor imageProcessor;
// 
// 	// std::vector<cv::Mat> images = imageProcessor.GetImagesFromFolder(iamgesFolderPath);
// 	// int index = 0;
// 	// for (const auto& image : images)
// 	// {
// 	// 	std::string windowName = "Image " + std::to_string(++index);
// 	   
// 	// 	cv::Mat processedImage = imageProcessor.ProcessImage(image, ResolutionType::SVGA, true);
// 	   
// 	// 	 cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
// 	// 	 cv::imshow(windowName, processedImage);
// 	// }
// 
// 	 VideoPlayer videoPlayer(videoPath, ResolutionType::HD, imageProcessor);
// 	 videoPlayer.PlayVideo();
// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 	// JsonParser parser("resources/dataset/train/");
// 	// parser.loadDataFromJson("_annotations.coco.json");
// 
// 	cv::waitKey(0);
// 	cv::destroyAllWindows();
// 
// 	return 0;
// }
// 
   