#include <opencv2/opencv.hpp>  
#include <iostream>  

cv::Mat gamma_cor(const cv::Mat& src, double gamma) {
    gamma = std::max(gamma, 0.0001);
    cv::Mat dst;
    src.convertTo(dst, -1, 1.0, 0);
    dst.convertTo(dst, CV_32F, 1.0 / 255.0);
    cv::pow(dst, gamma, dst);
    dst.convertTo(dst, CV_8U, 255.0);

    return dst;
}

int main() {
    cv::Mat image = cv::imread("pic1.png", cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return -1;
    }

    double gamma = 0.5;
    cv::Mat gamma_corr = gamma_cor(image, gamma);

    cv::imshow("Gamma Corrected", gamma_corr);
    cv::waitKey(0);

    return 0;
}