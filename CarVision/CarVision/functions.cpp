#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/cudacodec.hpp>

#include "functions.hpp"

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
    std::map<ResolutionType, Resolution> resolutionMap = CreateResolutionsMap();
    cv::Size newSize(std::get<0>(resolutionMap[resolution]), std::get<1>(resolutionMap[resolution]));
    std::vector<cv::Rect> bodies;
    cv::cuda::GpuMat gpuImg, grayImg;

    // Resize the image to desired resolution
    cv::resize(img, img, newSize);

    // Upload image to GPU
    gpuImg.upload(img);

    // Convert image to grayscale on GPU
    cv::cuda::cvtColor(gpuImg, grayImg, cv::COLOR_BGR2GRAY);

    // HOG descriptor with default people detector
    cv::Ptr<cv::cuda::HOG> hog = cv::cuda::HOG::create();
    hog->setSVMDetector(hog->getDefaultPeopleDetector());

    // Detect people in the image
    hog->detectMultiScale(grayImg, bodies);

    // Download processed image back to CPU
    cv::Mat processedImg;
    grayImg.download(processedImg);

    // Draw rectangles around detected people
    for (const auto& rect : bodies)
    {
        cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(255, 0, 255), 2);
    }

    return img;
}

int PlayVideo(const std::string videoPath = "use_deviceID", ResolutionType resolution = HD)
{
    cv::Mat frame;
    cv::Mat processedFrame;
    cv::VideoCapture cap;

    // open video from drive
    if (videoPath != "use_deviceID")
    {
        cap.open(videoPath);
    }
    // open video from live source
    else
    {
        int deviceID = 0; // 0 = open default camera
        int apiID = cv::CAP_ANY; // 0 = autodetect default API
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
        cap.read(frame);
        // check if we succeeded
        if (frame.empty())
        {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        processedFrame = ProcessImage(frame, resolution);

        // show live and wait for a key with timeout long enough to show images
        imshow("Live", processedFrame);
        if (cv::waitKey(5) >= 0)
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
