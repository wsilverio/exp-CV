#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat img = imread("../images/Lenna.png");
    // Mat img = imread("../images/CH03/Fig0338(a)(blurry_moon).tif", 0);

    imshow("original", img);
    imwrite("original.png", img);

    // {{ 0, 1, 0}, { 1,-4, 1}, { 0, 1, 0}},
    // {{ 1, 1, 1}, { 1,-8, 1}, { 1, 1, 1}},
    // {{ 0,-1, 0}, {-1, 4,-1}, { 0,-1, 0}},
    // {{-1,-1,-1}, {-1, 8,-1}, {-1,-1,-1}}

    Mat kernel[4];

    kernel[0] = (Mat_<char>(3,3) <<   /*Laplaciano - 2ª derivada*/ 
    0, 1, 0,
    1,-4, 1,
    0, 1, 0);

    kernel[1] = -kernel[0];
    // kernel[1] = (Mat_<char>(3,3) <<    /*negativo*/
    // 0, -1, 0,
    // -1, 4,-1,
    // 0, -1, 0);

    kernel[2] = (Mat_<char>(3,3) <<    /*diagonais*/
    1, 1, 1,
    1,-8, 1,
    1, 1, 1);

    kernel[3] = -kernel[2];
    // kernel[3] = (Mat_<char>(3,3) <<    /*negativo*/
    // -1,-1,-1,
    // -1, 8,-1,
    // -1,-1,-1);

    Mat result;
    // for (int i = 0; i < 4; ++i){
    //     filter2D(img, result, img.depth(), kernel[i]);
    //     imshow("filtro2D[" + to_string(i) + "]", result);
    //     imshow("img - filtro2D[" + to_string(i) + "]", img - result);    
    //     imshow("img + filtro2D[" + to_string(i) + "]", img + result);    

    //     imwrite("filtro2D[" + to_string(i) + "].png", result);
    //     imwrite("img-filtro2D[" + to_string(i) + "].png", img - result);    
    //     imwrite("img+filtro2D[" + to_string(i) + "].png", img + result);
    // }

    // Laplacian(img, result, CV_16S, 5);
    // convertScaleAbs(result, result, 1);
    // imshow("Laplacian", result);
    // Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )

    // imshow("Laplacian", result);

    waitKey();

    return 0;
}