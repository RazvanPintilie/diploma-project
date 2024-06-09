#include "../inc/JsonParser.hpp"
#include "../inc/Detector.h"

int main()
{
	// cv::cuda::printCudaDeviceInfo(0);

	std::vector<std::pair<cv::Mat, std::vector<cv::Rect>>> anotatedImages;
	JsonParser parser("resources/dataset/train/");
	anotatedImages = parser.loadDataFromJson("_annotations.coco.json");

	//cv::Mat image = anotatedImages.at(0).first;
	//cv::imshow("test", image);

	cv::Mat image = cv::imread("resources/moc/val/images/2007_005064.jpg");
	Detector detector;
	detector.Initialize(0, 416, 416, "resources/moc/voc_classes.txt");
	// detector.Train("resources/moc", ".jpg", 30, 4, 0.001, "weights/detector.pt", "weights/yolo4_tiny.pt");

	detector.LoadWeight("weights/detector.pt");
	detector.Predict(image, true, 0.1);

	// speed test
	int64 start = cv::getTickCount();
	int loops = 10;
	for (int i = 0; i < loops; i++)
	{
		detector.Predict(image, false);
	}

	double duration = (cv::getTickCount() - start) / cv::getTickFrequency();
	std::cout << duration / loops << " s per prediction" << std::endl;

	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}