#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main(int argc, char** argv) {  
    cv::Mat image = cv::imread("miku.jpg", cv::IMREAD_COLOR);  
  
    cv::Mat hsvImage;  
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);  
  
    hsvImage.at<cv::Vec3b>(0, 0)[0] += 30;  
    hsvImage.at<cv::Vec3b>(0, 0)[0] = hsvImage.at<cv::Vec3b>(0, 0)[0] % 180;
  
    cv::namedWindow("HSV Image", cv::WINDOW_AUTOSIZE);  
    cv::imshow("HSV Image", hsvImage);  
  
    cv::waitKey(0);  
  
    return 0;  
}