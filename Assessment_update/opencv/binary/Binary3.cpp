#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main(int argc, char** argv) {  
    const std::string inputPath = "src.jpg";  
    const std::string outputPath = "binary3.jpg";  
    const int threshold = 128;
  
    cv::Mat src = cv::imread(inputPath, cv::IMREAD_COLOR);  
    if (src.empty()) {  
        std::cerr << "ERROR" << inputPath << std::endl;  
        return -1;  
    }  
  
    cv::Mat gray;  
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);  
  
    cv::Mat dst(gray.size(), gray.type());  
  
    for (int y = 0; y < gray.rows; ++y) {  
        for (int x = 0; x < gray.cols; ++x) {  
            uchar pixelValue = gray.at<uchar>(y, x);  
            dst.at<uchar>(y, x) = pixelValue > threshold ? 255 : 0;  
        }  
    }  
  
    cv::imwrite(outputPath, dst);  
  
    return 0;  
}