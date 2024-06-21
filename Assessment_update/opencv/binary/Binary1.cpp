#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main(int argc, char** argv) {  
    const std::string inputPath = "src.jpg";  
    const std::string outputPath = "binary1.jpg";  
    const int threshold = 128; 
  
    cv::Mat src = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);  
    if (src.empty()) {  
        std::cerr << "ERROR" << inputPath << std::endl;  
        return -1;  
    }  
  
    cv::Mat dst = src.clone();  
  
    cv::MatIterator_<cv::Vec3b> it, end;  
    for (it = dst.begin<cv::Vec3b>(), end = dst.end<cv::Vec3b>(); it != end; ++it) {  
        cv::Vec3b& pixel = *it;  
  
        pixel[0] = pixel[0] > threshold ? 255 : 0;
        pixel[1] = pixel[1] > threshold ? 255 : 0;
        pixel[2] = pixel[2] > threshold ? 255 : 0;
    }  
  
    cv::imwrite(outputPath, dst);  
    return 0;  
}