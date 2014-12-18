#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){

    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    // namedWindow("Video", CV_WINDOW_AUTOSIZE);
    namedWindow("sobel x", CV_WINDOW_AUTOSIZE);
    namedWindow("sobel y", CV_WINDOW_AUTOSIZE);
    namedWindow("laplaciano", CV_WINDOW_AUTOSIZE);
    namedWindow("result abs", CV_WINDOW_AUTOSIZE);
    namedWindow("result", CV_WINDOW_AUTOSIZE);
    namedWindow("x+y", CV_WINDOW_AUTOSIZE);

    while(1) {
        Mat img;
        cap >> img;

        cvtColor(img, img, CV_BGR2GRAY);

        int m = 7;
        GaussianBlur(img, img, Size(m, m), (m/2.0)*0.5);

        Mat result;

        Laplacian(img, result, CV_16S, 3);
        convertScaleAbs(result, result);
        imshow("laplaciano", result);

        // Sobel(img, result, CV_16S, 1, 0, CV_SCHARR, 1, 0, BORDER_DEFAULT);
        // Sobel(img, result, CV_16S, 1, 1, 3, 1, 0, BORDER_DEFAULT);
        // convertScaleAbs(result, result);

        Mat x, y;
        Sobel(img, x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
        Sobel(img, y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);

        addWeighted(x, 0.5, y, 0.5, 0, result);
        // add(x, y, result);
        convertScaleAbs(result, result);
        imshow("result abs", result);

        convertScaleAbs(x, x);
        convertScaleAbs(y, y);

        imshow("sobel x", x);
        imshow("sobel y", y);

        // flip(img, img, 1);

        // imshow("Video", result);
        // imshow("Video", Scalar(255) - result);

        addWeighted(x, 0.5, y, 0.5, 0, result);

        imshow("x+y", (x + y));
        imshow("result", result);

        if(waitKey(30) >= 0) break;

    }

    // Mat img = imread("../images/desenho.jpg");
    // imshow("img", img);
    // imwrite("img.png", img);
    // Mat result, x, y;
    // Sobel(img, x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    // Sobel(img, y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    // addWeighted(x, 0.5, y, 0.5, 0, result);
    // convertScaleAbs(result, result);
    // imshow("Sobel", result);
    // imwrite("Sobel.png", result);
    // waitKey();

    return 0;
}