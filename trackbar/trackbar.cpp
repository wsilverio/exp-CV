#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

Mat img;
int valor_slide = 0;
string end = "../images/real.jpg";

void trackbar(int, void *){

    img = imread(end, 0);
    
    for (int j = 0; j < valor_slide; ++j){
        for (int i = 0; i < img.rows; ++i){
            img.at<char>(i, j) = 255 - img.at<char>(i, j);
        }
    }

    imshow("IMG", img);

}

int main(void){
 
    namedWindow("IMG", WINDOW_AUTOSIZE);

    img = imread(end, 0);

    createTrackbar("neg cols: ", "IMG", &valor_slide, img.cols, trackbar);
    trackbar(valor_slide, 0);

    waitKey();

    return 0;
}