#include "VideoPlayer.hpp"

VideoPlayer::VideoPlayer(const std::string& videoPath, ResolutionType resolution, ImageProcessor imageProcessor)
	: videoPath(videoPath), resolution(resolution), imageProcessor(imageProcessor) {}

int VideoPlayer::PlayVideo()
{
	static unsigned int framesCounter = 0;
	cv::Mat frame, processedFrame;
	cv::VideoCapture cap;

	// open video 
	cap.open(this->videoPath);
	// cap.open(1);

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
		cap.read(frame);
		// check if we succeeded
		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		// process only 1/3 of the frames
		if ((framesCounter++) % 3 == 0)
		{
			processedFrame = this->imageProcessor.ProcessImage(frame, this->resolution);
		}

		// show live and wait for a key with timeout long enough to show images
		cv::imshow("Live", processedFrame);
		if (cv::waitKey(3) >= 0)
		{
			break;
		}
	}

	cap.release();
	cv::destroyAllWindows();

	return 0;
}
