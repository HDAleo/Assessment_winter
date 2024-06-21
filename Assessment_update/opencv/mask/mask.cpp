#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double EuDis(Point2f pt1, Point2f pt2)
{
    return sqrt((pt2.x - pt1.x) * (pt2.x - pt1.x) + (pt2.y - pt1.y) * (pt2.y - pt1.y));
}

int main()
{
    Mat src = imread("../src.jpg");
    if (src.empty())
    {
        cout << "ERROR" << endl;
        system("pause");
        return -1;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    Mat gaussian;
    GaussianBlur(gray, gaussian, Size(3, 3), 0);

    Mat thresh;
    threshold(gaussian, thresh, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat open;
    morphologyEx(thresh, open, MORPH_OPEN, kernel);

    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(7, 7));
    Mat close;
    morphologyEx(open, close, MORPH_CLOSE, kernel1);

    Mat over;
    bitwise_not(close, over);

    vector<vector<Point>> contours;
    findContours(over, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Point> srcPts;

    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);

        if (area > 10000)
        {
            double peri = arcLength(contours[i], true);

            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            srcPts.emplace_back(conPoly[i][0]);
            srcPts.emplace_back(conPoly[i][1]);
            srcPts.emplace_back(conPoly[i][2]);
            srcPts.emplace_back(conPoly[i][3]);
        }
    }

    int width = src.cols / 2;
    int height = src.rows / 2;
    int T_L, T_R, B_R, B_L;

    for (int i = 0; i < srcPts.size(); i++)
    {
        if (srcPts[i].x < width && srcPts[i].y < height)
        {
            T_L = i;
        }
        if (srcPts[i].x > width && srcPts[i].y < height)
        {
            T_R = i;
        }
        if (srcPts[i].x > width && srcPts[i].y > height)
        {
            B_R = i;
        }
        if (srcPts[i].x < width && srcPts[i].y > height)
        {
            B_L = i;
        }
    }
    double LeftHeight = EuDis(srcPts[T_L], srcPts[B_L]);
    double RightHeight = EuDis(srcPts[T_R], srcPts[B_R]);
    double MaxHeight = std::max(LeftHeight, RightHeight);

    double UpWidth = EuDis(srcPts[T_L], srcPts[T_R]);
    double DownWidth = EuDis(srcPts[B_L], srcPts[B_R]);
    double MaxWidth = std::max(UpWidth, DownWidth);

    std::array<Point2f, 4> SrcAffinePts = { Point2f(srcPts[T_L]), Point2f(srcPts[T_R]), Point2f(srcPts[B_R]), Point2f(srcPts[B_L]) };
    std::array<Point2f, 4> DstAffinePts = { Point2f(0, 0), Point2f(MaxWidth, 0), Point2f(MaxWidth, MaxHeight), Point2f(0, MaxHeight) };

    Mat M = getPerspectiveTransform(SrcAffinePts, DstAffinePts);

    Mat DstImg;
    warpPerspective(src, DstImg, M, Point(MaxWidth, MaxHeight));
    imshow("Dst", DstImg);

    namedWindow("src", WINDOW_NORMAL);
    imshow("src", src);
    waitKey(0);
    destroyAllWindows();

    system("pause");
    return 0;
}