#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
	char texto[] = "Lorem Ipsum";
	int tam = 32;

	Mat img(Size(600, 500), CV_8UC3, Scalar::all(255));

	namedWindow("img", WINDOW_AUTOSIZE);

	int y = 0;
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_PLAIN, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_DUPLEX, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_COMPLEX, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_TRIPLEX, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(0), 1, 8);
	putText(img, texto, Point (50, y+=50), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(0), 1, 8);

	// putText(img, texto, Point (50, 50), FONT_HERSHEY_SIMPLEX, double fontScale, Scalar color, int thickness=1, int lineType=LINE_8, bool bottomLeftOrigin=false );

	imshow("img", img);

	waitKey();

	return 0;
}