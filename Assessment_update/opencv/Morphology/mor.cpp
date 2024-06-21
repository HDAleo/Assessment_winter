#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main() {  
    cv::Mat src = cv::imread("mor.png", cv::IMREAD_GRAYSCALE);  
  
    cv::Mat binaryImage;  
    cv::threshold(src, binaryImage, 127, 255, cv::THRESH_BINARY);  
  
    int kernelSize = 5;  
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));  

    cv::Mat erodedImage;  
    cv::erode(binaryImage, erodedImage, kernel);  
   
    cv::Mat dilatedImage;  
    cv::dilate(binaryImage, dilatedImage, kernel);  
  
    cv::Mat openedImage;  
    cv::morphologyEx(binaryImage, openedImage, cv::MORPH_OPEN, kernel);  
  

    cv::Mat closedImage;  
    cv::morphologyEx(binaryImage, closedImage, cv::MORPH_CLOSE, kernel);  
 
    cv::Mat resizedImages[5];  
    for (int i = 0; i < 5; ++i) {  
        resizedImages[i] = binaryImage.clone();
        if (i > 0) {  
            cv::resize(resizedImages[i], resizedImages[i], binaryImage.size());  
        }  
    }  
    resizedImages[1] = erodedImage;  
    resizedImages[2] = dilatedImage;  
    resizedImages[3] = openedImage;  
    resizedImages[4] = closedImage;

    cv::Mat result;  
    cv::hconcat(resizedImages, 5, result);  

    cv::imshow("Images", result);  
    cv::waitKey(0);  
  
    return 0;  
}