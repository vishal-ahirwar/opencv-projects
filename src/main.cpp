// copyright(c)2022 Vishal Ahirwar.
#include <iostream>
#include<vector>
#include <opencv2/opencv.hpp>
#include<ctime>
// #define IMAGEFILES
// #define VIDEOFILES
// #define READVIDEOFILE
#define BASIC

void GetContours(cv::Mat , cv::Mat );

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
    const char *path{"../assets/images/color-shapes.png"};
    /**
        cv::Mat img{cv::imread(path)}, imgGray, imgCanny, imgDia, imgErode;
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY); // Gray
        cv::GaussianBlur(img, imgGray, cv::Size(25, 25), 4, 0);
        cv::Canny(imgGray, imgCanny, 25, 75);
        cv::Mat Kernal = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::dilate(imgCanny, imgDia, Kernal);
        cv::erode(imgDia, imgErode, Kernal);
        cv::namedWindow(path, cv::WINDOW_GUI_EXPANDED);
        cv::imshow(path, imgErode);
    **/
    cv::Mat img, imgBlur, imgCanny,imgHSV,mask;
    // cv::VideoCapture cap(0);
    /**
        cv::resize(cv::imread(path),img,cv::Size(),0.7,0.5);

        cv::rectangle(img,cv::Point(90,90),cv::Point(790,170),cv::Scalar(255,0,0),cv::FILLED);
        cv::putText(img,"Hello, World to opencv C++ by Vishal.",cv::Point(100,130),cv::FONT_HERSHEY_TRIPLEX,1,cv::Scalar(255,255,255),1);
        cv::imshow(path,img);
    **/
         int hmin{}, smin{}, vmin{};
         int hmax{}, smax{}, vmax{};

         cv::namedWindow("Detection Color", (800, 200));
        //  cv::cvtColor(img, imgHSV, cv::COLOR_RGB2HSV);
         cv::createTrackbar("hue MIN", "Detection Color", &hmin, 255);
         cv::createTrackbar("sat MIN", "Detection Color", &smin, 255);
         cv::createTrackbar("val MIN", "Detection Color", &vmin, 255);
         cv::createTrackbar("hue MAX", "Detection Color", &hmax, 255);
         cv::createTrackbar("sat MAX", "Detection Color", &smax, 255);
         cv::createTrackbar("val MAX", "Detection Color", &vmax, 255);
    /**

         while (true)
         {
             // cap.read(img);

             cv::namedWindow(path, cv::WINDOW_GUI_EXPANDED);
             cv::putText(imgHSV,"FRAMES HAS BEEN RUN :",cv::Point(hmin,hmax),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(255,255,255));
             cv::imshow(path, imgHSV);
             if (cv::waitKey(1) == 27)
                 break;
         };
     **/
    cv::Mat src, imgDi,imgContours;
    cv::VideoCapture cap(0);
    cv::Mat Kernal{cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3))};
    // double FPS{};
    while (true)
    {
     //   time(now);

        cap.read(src);

        // printf("trackbars value : %d %d\n", hmin, hmax);
        cv::cvtColor(src, img, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(img, imgBlur, cv::Size(13, 13), 3, 0);
        cv::Canny(imgBlur, imgCanny, 25, 75);
        cv::dilate(imgCanny, imgDi, Kernal);

        GetContours(imgDi,imgContours);
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(img, lower, upper, mask);

        cv::imshow("Camera 01 running ...", mask);

        if (cv::waitKey(1) == 27)
            break;
    }
#endif
    return 0;
};
void GetContours(cv::Mat img, cv::Mat out)
{
    std::vector<std::vector<cv::Point>> contours{};
    std::vector<cv::Vec4i> hierarchy{};

    cv::findContours(img,contours,hierarchy,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(out,contours,-1,cv::Scalar(255,0,0),10);
}
