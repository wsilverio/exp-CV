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

    // vector<Mat> bgr;
    // split(img, bgr);

    // imshow("B", bgr[0]);
    // imshow("G", bgr[1]);
    // imshow("R", bgr[2]);

    // for (int i = 0; i < bgr.size(); i++){
    //     bgr[i] = 255 - bgr[i];
    // }

    // merge(bgr, img);

    imshow("negativo", Scalar(255, 255, 255) - img);
    imwrite("negativo.png", Scalar(255, 255, 255) - img);

    waitKey();

    return 0;
}