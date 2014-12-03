#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

int main(void){
    Mat img = imread("../images/CH03/Fig0326(a)(embedded_square_noisy_512).tif", 0);
    imshow("img", img);
    imwrite("img.png", img);

    Mat equa;
    equalizeHist(Scalar(255) - img, equa);
    imshow("equa", Scalar(255) - (equa - img));
    imwrite("equa-img.png", Scalar(255) - (equa - img));

    for (int i = 0; i < img.rows; ++i){
        for (int j = 0; j < img.cols; ++j){
            if(img.at<char>(i, j) < 4 || img.at<char>(i, j) > 10){
                img.at<char>(i, j) = 0;
            }else{
                img.at<char>(i, j) = 255;
            }
        }
    }

    imshow("bit-a-bit", img);
    imwrite("bit_a_bit.png", img);

    waitKey();

    return 0;
}