#include <opencv2/opencv.hpp>  
#include <vector>  
#include <random> 
#include <iostream>

using namespace cv;
using namespace std;
  
int main() {  
    cv::Mat srcMat = imread("count.jpg");
    cv::Mat resMat;
	cv::Mat resover;
	cv::Mat resover_dec;
	cv::Mat resover_sign;
	cv::Mat Matstate;
    cv::Mat center;
    cv::Mat gray;  

    std::default_random_engine generator;  
    std::uniform_int_distribution<int> colorDistribution(0, 255);  

    cv::cvtColor(srcMat, gray, cv::COLOR_BGR2GRAY);  
	cv::threshold(gray, resMat, 100, 255, THRESH_OTSU);
	cv::bitwise_not(resMat, resover);
	cv::connectedComponentsWithStats(resover, resover_sign, Matstate, center, 8, CV_32S);

	int totalClips = 0;
	int i;
    int line=0;
	line = Matstate.rows;

    for(i=0;i< Matstate.rows;i++){
        if (Matstate.at<int>(i, 4) >= 2000&& Matstate.at<int>(i, 4)<=8000){
            cv::Rect rect;

            rect.x = Matstate.at<int>(i, 0);
			rect.y = Matstate.at<int>(i, 1);
			rect.width = Matstate.at<int>(i, 2);
			rect.height = Matstate.at<int>(i, 3);

            int b = colorDistribution(generator);  
            int g = colorDistribution(generator);  
            int r = colorDistribution(generator);  

            cv::rectangle(srcMat, rect,cv::Scalar(b, g, r),2,8,0); 

            std::stringstream ss;  
            ss << " " << (++totalClips);  
            cv::putText(srcMat, ss.str(), cv::Point(rect.x + 5, rect.y + 20),  
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(b, g, r), 2);  
        }
    }
    
    cv::putText(srcMat, "Total clips: " + std::to_string(totalClips), cv::Point(10, 30),  
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 200), 2);  
  
    cv::imshow("Clips", srcMat);  
  
    cv::waitKey(0);  
    
    return 0;  
}