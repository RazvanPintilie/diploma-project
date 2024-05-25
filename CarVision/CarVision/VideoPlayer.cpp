#include "VideoPlayer.hpp"

VideoPlayer::VideoPlayer(const std::string& videoPath, ResolutionType resolution, ImageProcessor imageProcessor)
	: videoPath(videoPath), resolution(resolution), imageProcessor(imageProcessor){}

int VideoPlayer::PlayVideo()
{
    cv::Mat frame, processedFrame;
    cv::VideoCapture cap;

    // open video 
    cap.open(this->videoPath);

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

        processedFrame = this->imageProcessor.ProcessImage(frame, this->resolution);

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", processedFrame);
        if (cv::waitKey(1) >= 0)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
