#include "functions.hpp"

std::map<ResolutionType, Resolution> CreateResolutionsMap()
{
	std::map<ResolutionType, Resolution> resolutionMap;

	// Add FHD resolution to the map
	resolutionMap[FHD] = std::make_tuple(1920, 1080);
	 
	// Add HD resolution to the map
	resolutionMap[HD] = std::make_tuple(1280, 720);

	// Add SVGA resolution to the map
	resolutionMap[SVGA] = std::make_tuple(800, 600);

	return resolutionMap;
}

std::vector<cv::Mat> GetImagesFromFolder(std::string folderPath)
{
	std::vector<cv::String> imagePaths;
	std::vector<cv::Mat> images;

	// Get list of all image files in the directory
	cv::glob(folderPath + "*.jpg", imagePaths);

	// Check if images were found
	if (imagePaths.empty())
	{
		std::cout << "No images found in folder: " << folderPath << std::endl;
	}

	for (const auto& imgPath : imagePaths)
	{
		cv::Mat img = cv::imread(imgPath);
		images.push_back(img);
	}

	return images;
}

cv::Mat ProcessImage(cv::Mat img, ResolutionType resolution = HD)
{
	// Process the image 
	// cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	std::map<ResolutionType, Resolution> resolutionMap = CreateResolutionsMap();
	std::vector<cv::Rect> bodies;
	cv::HOGDescriptor hog;

	// resize the image to desired resolution
	cv::resize(img, img, cv::Size(std::get<0>(resolutionMap[resolution]), std::get<1>(resolutionMap[resolution])));

	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
	hog.detectMultiScale(img, bodies, 0, cv::Size(2, 2), cv::Size(0, 0), 1.05, 2);

	for (int i = 0; i < bodies.size(); i++)
	{
		cv::Mat imgCrop = img(bodies[i]);
		// imwrite("resources/output/" + std::to_string(i) + ".png", imgCrop);
		rectangle(img, bodies[i].tl(), bodies[i].br(), cv::Scalar(0, 255, 255), 2);
	}

	return img;
}


int PlayVideo(const std::string videoPath = "use_deviceID", ResolutionType resolution = HD)
{
	cv::Mat frame;
	cv::Mat processedFrame;
	cv::VideoCapture cap(0);

	// open video from drive
	if (videoPath != "use_deviceID")
	{
		cap.open(videoPath);
	}
	// open video from live source
	else
	{
		// OR advance usage: select any API backend
		int deviceID = 0; // 0 = open default camera
		int apiID = cv::CAP_ANY; // 0 = autodetect default API
		// open selected camera using selected API
		cap.open(deviceID, apiID);
	}

	// check if we succeeded
	if (!cap.isOpened())
	{
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	std::cout << "Start grabbing" << std::endl << "Press any key to terminate" << std::endl;
	for (;;)
	{
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// resize the frame to a specific size

		processedFrame = ProcessImage(frame, resolution);

		// show live and wait for a key with timeout long enough to show images
		imshow("Live", processedFrame);
		if (cv::waitKey(5) >= 0)
		{
			break;
		}
	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	cap.release();
	cv::destroyAllWindows();

	return 0;
}

