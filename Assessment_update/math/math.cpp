#include <opencv2/opencv.hpp>  
#include <vector>  

int main() {
    cv::Mat image = cv::imread("Julia.jpg", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat binary;
    cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); ++i) { 
        cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1); 
        cv::drawContours(mask, contours, i, cv::Scalar(255), cv::FILLED);
        cv::Mat region = cv::Mat::zeros(image.size(), image.type());
        image.copyTo(region, mask);  
        std::string filename = "region_" + std::to_string(i) + ".jpg";
        cv::imwrite(filename, region);
        std::cout << "Saved " << filename << std::endl;
    }
    return 0;
}