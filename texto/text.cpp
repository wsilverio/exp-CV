#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
	char texto[] = "";
	int tam = 32;

	Mat img(Size(400, 100), CV_8UC3, Scalar(255, 255, 255));

	namedWindow("img", WINDOW_AUTOSIZE);

	CvFont font = fontQt("FreeMono", tam, Scalar(0, 72, 143, 0));
	addText(img, "Lorem Ipsum", Point(50, 50), font);

	imshow("img", img);

	waitKey();

	return 0;
}