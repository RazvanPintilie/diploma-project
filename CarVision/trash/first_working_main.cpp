#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

///////////////  Project 3 - License Plate Detector //////////////////////

int main() {

	Mat img;
	//VideoCapture cap(0);

	//CascadeClassifier plateCascade;
	//plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	//if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	//vector<Rect> plates;

	//while (true) {

	//	cap.read(img);
	//	plateCascade.detectMultiScale(img, plates, 1.1, 10);

	//	for (int i = 0; i < plates.size(); i++)
	//	{
	//		Mat imgCrop = img(plates[i]);
	//		//imshow(to_string(i), imgCrop);
	//		imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop);
	//		rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
	//	}

	//	imshow("Image", img);
	//	waitKey(1);
	//}

	std::string folderPath = "resources/pedestrians/test_images/";
	std::vector<cv::String> imagePaths;

	// Get list of all image files in the directory
	cv::glob(folderPath + "*.jpg", imagePaths);


	// Check if images were found
	if (imagePaths.empty()) 
	{
		std::cout << "No images found in folder: " << folderPath << std::endl;
		return -1;
	}

	// Iterate over each image file path and read the image
	for (const auto& imgPath : imagePaths) 
	{
		cv::Mat img = cv::imread(imgPath);
		if (img.empty()) 
		{
			std::cout << "Could not read the image: " << imgPath << std::endl;
			continue;
		}

		// Display the image (optional)
		//cv::imshow("Image", img);
		//cv::waitKey(0); // Wait for a key press

		// Process the image (you can add your processing code here)
		// For example: cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

		vector<Rect> bodies;

		HOGDescriptor hog;
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		hog.detectMultiScale(img, bodies, 0, Size(2, 2), Size(0, 0), 1.05, 2);

		for (int i = 0; i < bodies.size(); i++)
		{
			Mat imgCrop = img(bodies[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("resources/plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, bodies[i].tl(), bodies[i].br(), Scalar(255, 0, 255), 3);
		}

		imshow("Image", img);
		cv::waitKey(0);
	}


	std::string imgPath = "resources/pedestrians/test_images/pedestrians_1.jpg";
	img = cv::imread(imgPath);


	CascadeClassifier plateCascade;
	CascadeClassifier bodyCascade;

	//plateCascade.load("resources/cascades/haarcascade_russian_plate_number.xml");
	bodyCascade.load("resources/data/haarcascades_cuda/haarcascade_upperbody.xml");



	// bodyCascade.load("resources/data/hogcascades/hogcascade_pedestrians.xml");


	vector<Rect> plates;
	//vector<Rect> bodies;

	//HOGDescriptor hog;
	//hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	//hog.detectMultiScale(img, bodies, 0, Size(2, 2), Size(0, 0), 1.05, 2);



	////static double scaleFactor = 1.1;
	////static const int minNeighbors = 2;
	////static const cv::Size minSize(30, 30);
	////static const cv::Size maxSize;

	////// plateCascade.detectMultiScale(img, plates, 1.1, 10);
	////bodyCascade.detectMultiScale(img, bodies, scaleFactor, minNeighbors, cv::CASCADE_SCALE_IMAGE, minSize, maxSize);

	//for (int i = 0; i < bodies.size(); i++)
	//{
	//	Mat imgCrop = img(bodies[i]);
	//	//imshow(to_string(i), imgCrop);
	//	imwrite("resources/plates/" + to_string(i) + ".png", imgCrop);
	//	rectangle(img, bodies[i].tl(), bodies[i].br(), Scalar(255, 0, 255), 3);
	//}

	//imshow("Image", img);
	//cv::waitKey(0);

	return 0;
}