#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main(int argc, char** argv) {  
    const std::string inputPath = "src.jpg";  
    const std::string outputPath = "canny.jpg";

    cv::Mat Image = cv::imread(inputPath, cv::IMREAD_COLOR);  

    if (Image.empty()) {  
        std::cerr << "ERROR" << std::endl;  
        return -1;  
    }  

    
    cv::Mat grayImage;  
    cv::cvtColor(Image, grayImage, cv::COLOR_BGR2GRAY);  

    cv::Mat dst(Image.size(), Image.type());
    
    cv::Mat blurredImage;  
    cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0);  
  
    cv::Mat edges;  
    cv::Canny(blurredImage, edges, 50, 150);  
    
    cv::namedWindow("Original Image", cv::WINDOW_NORMAL);  
    cv::imshow("Original Image", Image);  
  
    cv::namedWindow("Edge Image", cv::WINDOW_NORMAL);  
    cv::imshow("Edge Image", edges);  
   
    cv::waitKey(0);  
    cv::destroyAllWindows();  

    return 0;  
}