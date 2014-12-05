#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

int main(void){
	Mat img = imread("../images/Lenna.png");
    // resize(img, img, Size(), 0.15, 0.15);
	imshow("original", img);
	imwrite("original.png", img);

	imshow("negativo", Scalar(255, 255, 255) - img);
	imwrite("negativo.png", Scalar(255, 255, 255) - img);

	waitKey();

	return 0;
}