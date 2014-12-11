#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){

	VideoCapture cap(0);
	if(!cap.isOpened())
		return -1;

	namedWindow("Video", CV_WINDOW_AUTOSIZE);

	while(1) {
		Mat img;
		cap >> img;
		cvtColor(img, img, CV_BGR2GRAY);

		// blur(img, img, Size(3, 3));
		// Laplacian(img, img, CV_16S, 3);
		Mat result;
		Sobel(img, result, CV_16S, 1, 0, CV_SCHARR, 1, 0, BORDER_DEFAULT);
		// Sobel(img, result, CV_16S, 1, 1, 3, 1, 0, BORDER_DEFAULT);
		// Sobel(img, img, CV_16S, 1, 1, 3, 1, 0, BORDER_DEFAULT);
		// Sobel(img, img, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
		// Sobel(img, img, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
		convertScaleAbs(result, result);
		// Sobel(src, dst, ddepth, dx, dy, ksize=3, scale=1, delta=0, BORDER_DEFAULT );

		// flip(img, img, 1);
		
		imshow("Video", Scalar(255) - result);
		if(waitKey(30) >= 0) break;

	}

	// Mat img = imread("../images/CH03/Fig0342(a)(contact_lens_original).tif", 0);

	// imshow("img", img);
	// imwrite("img.png", img);

	// Sobel(img, img, img.depth(), 1, 1, 3, 1, 0, BORDER_DEFAULT);
	// convertScaleAbs(img, img);
	// Sobel(src, dst, ddepth, dx, dy, ksize=3, scale=1, delta=0, BORDER_DEFAULT );
	// imshow("Sobel", img);

	// waitKey();

	return 0;
}