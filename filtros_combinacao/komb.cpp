#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
	Mat img = imread("../images/CH03/Fig0343(a)(skeleton_orig).tif");

	imshow("img", img);
	// imwrite("img.png", img);

	Mat kernel = (Mat_<char>(3,3) <<
		-1,-1,-1,
		-1, 8,-1,
		-1,-1,-1 );

	Mat lapla;
	filter2D(img, lapla, img.depth(), kernel);
	// convertScaleAbs(lapla, lapla);
	// Laplacian(img, lapla, CV_16S, 5);
	imshow("Laplaciano", lapla);

	cout << CV_16S;

	waitKey();

	return 0;
}