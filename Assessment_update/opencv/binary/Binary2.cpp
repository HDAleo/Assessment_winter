#include <iostream>  
#include <opencv2/opencv.hpp>  
  
int main() {  
    const std::string inputPath = "src.jpg";  
    const std::string outputPath = "binary2.jpg";  

    cv::Mat src = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);  

    if (src.empty()) {  
        std::cerr << "ERROR" << inputPath << std::endl;  
        return -1;  
    }  
  
    cv::Mat dst(src.size(), src.type());  
  
    const int threshold = 128;  
  
    for (int y = 0; y < src.rows; ++y) {  
        for (int x = 0; x < src.cols; ++x) {  

            uchar* srcPixel = src.ptr<uchar>(y);  
            uchar* dstPixel = dst.ptr<uchar>(y);  
  
            dstPixel[x] = (srcPixel[x] > threshold) ? 255 : 0;  
        }  
    }  

    cv::imwrite(outputPath, dst);
    
    return 0;  
}