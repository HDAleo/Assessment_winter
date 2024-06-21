#include <opencv2/opencv.hpp>  
#include <complex>  
#include <cmath>  

using namespace cv;
using namespace std;

int mandelbrot(complex<double> c, int max_iter) {
    complex<double> z = 0;
    for (int n = 0; n < max_iter; ++n) {
        if (abs(z) > 2) return n;
        z = z * z + c;
    }
    return max_iter;
}


Vec3b colorEscapeTime(int iter, int max_iter) {

    double ratio = static_cast<double>(iter) / max_iter;
    int blue = static_cast<int>(255 * (1 - ratio));
    int red = static_cast<int>(255 * ratio);
    return Vec3b(red, 0, blue);
}

int main() {
    int width = 800, height = 800;
    int max_iter = 1000;
    double xmin = -2.0, xmax = 1.0; 
    double ymin = -1.5, ymax = 1.5;

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));
  
    for (int y = 0; y < height; ++y) {
        double cy = ymin + (ymax - ymin) * y / (height - 1);
        for (int x = 0; x < width; ++x) {
            double cx = xmin + (xmax - xmin) * x / (width - 1);
            complex<double> c(cx, cy);
            int iter = mandelbrot(c, max_iter);

            Vec3b color = colorEscapeTime(iter, max_iter);

            img.at<Vec3b>(y, x) = color;
        }
    }

    imshow("Mandelbrot Set", img);
    waitKey(0);

    return 0;
}