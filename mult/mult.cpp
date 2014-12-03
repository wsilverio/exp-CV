#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;


int main(void){
    
    RNG random;

    Mat img = imread("../images/multidao.jpg");

    Mat mask(Mat::zeros(img.size(), CV_8UC3));
    
    int raio = 50;
    int qtde = 1;

    for (int i = 0; i < qtde; i++){
        circle(mask, Point(random.uniform(raio, mask.cols - raio), random.uniform(raio, mask.rows - raio)), raio, Scalar(1, 1, 1), -1, 8, 0);
    }

    Mat resul;
    multiply(img, mask, resul); 
    imshow("multidao", resul);
    imwrite("multidao.jpg", resul);

    
    img = imread("../images/CH02/Fig0230(a)(dental_xray).tif");
    mask = imread("../images/CH02/Fig0230(b)(dental_xray_mask).tif");
    mask /= 255;

    // cout << mask;

    multiply(img, mask, resul);
    imshow("dente", img.mul(mask));
    imwrite("dente.jpg", img.mul(mask));

    waitKey();

    return 0;
}