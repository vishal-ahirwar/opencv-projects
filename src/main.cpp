// copyright(c)2022 Vishal Ahirwar.
#include <iostream>
#include <opencv2/opencv.hpp>
// #define IMAGEFILES
// #define VIDEOFILES
// #define READVIDEOFILE
// #define BASIC

int main()
{
#ifdef IMAGEFILES
    const char *path{"../assets/images/v101.png"};
    cv::Mat image{cv::imread(path)};
    if (image.empty())
    {
        std::cout << "Image path is wrong or maybe file is correpted!\n";
        std::cin.get();
        return -1;
    };
    cv::imshow(path, image);
    cv::waitKey(0);
#endif
// read video file
#ifdef VIDEOFILES
    //    #define READVIDEOFILE
#ifdef READVIDEOFILE
    cv::VideoCapture cap("../assets/videos/test.mp4");
#else
    cv::VideoCapture cap(0);
#endif
    cv::Mat image;
    while (true)
    {
        cap.read(image);
        if (image.empty())
        {
            std::cout << "Image path is wrong or maybe file is correpted!\n";
            std::cin.get();
            return -1;
        };
        cv::imshow("running front camera ", image);
        if (cv::waitKey(20) == 27)
            break;
    };
#endif

#ifdef BASIC
    const char *path{"../assets/images/v101.png"};
    cv::Mat img{cv::imread(path)}, imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_RGB2GRAY);
    cv::imshow("GRAY", imgGray);
    cv::waitKey(0);
#endif
    std::cout << "\nProgram Reached at the End!\n";
    return 0;
};
