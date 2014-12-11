#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
int valor_slide = 0;
string addrs = "../images/real.jpg";

void trackbar(int, void *){

    img = imread(addrs, 0);
    
    for (int j = 0; j < valor_slide; ++j){
        for (int i = 0; i < img.rows; ++i){
            img.at<char>(i, j) = 255 - img.at<char>(i, j);
        }
    }

    imshow("IMG", img);

}

int main(void){

    namedWindow("IMG", WINDOW_AUTOSIZE);

    img = imread(addrs, 0);

    createTrackbar("neg cols: ", "IMG", &valor_slide, img.cols, trackbar);
    trackbar(valor_slide, 0);

    waitKey();

    return 0;
}