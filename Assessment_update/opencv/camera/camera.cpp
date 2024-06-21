#include <opencv2/opencv.hpp>  
#include <iostream>  
  
int main(int argc, char** argv) {  
    cv::VideoCapture cap(0);  \

    if (!cap.isOpened()) {  
        std::cerr << "Error" << std::endl;  
        return -1;  
    }  
  
    cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);  
  
    while (true) {  
        cv::Mat frame;  
  
        if (!cap.read(frame)) {  
            std::cerr << "Error" << std::endl;  
            break;  
        }  
  
        cv::imshow("Camera Feed", frame);  
  
        if (cv::waitKey(30) == 'q') {  
            break;  
        }  
    }  
  
    cap.release();  
  
    cv::destroyAllWindows();  
  
    return 0;  
}