#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(void){
    
    // inicia um numero randomico com seed 1234
    RNG random(1234);

    Mat img = imread("../images/multidao.jpg");

    Mat mask(Mat::zeros(img.size(), CV_8UC3));
    
    int raio = 50;
    int qtde = 3;

    for (int i = 0; i < qtde; i++){
        random.next();
        circle(mask, Point(random.uniform(raio, mask.cols - raio), random.uniform(raio, mask.rows - raio)), raio, Scalar(1, 1, 1), -1, 8, 0);
    }

    Mat resul;
    multiply(img, mask, resul); 
    imshow("multidao", resul);
    imwrite("multidao.jpg", resul);

    img = imread("../images/CH02/Fig0230(a)(dental_xray).tif", 0);
    mask = imread("../images/CH02/Fig0230(b)(dental_xray_mask).tif", 0);
    
    // converte a máscara PB em binário
    mask /= 255; // 0-255 -> 0-1

    // cout << mask;

    multiply(img, mask, resul);
    imshow("dente", img.mul(mask));
    imwrite("dente.jpg", img.mul(mask));

    waitKey();

    return 0;
}