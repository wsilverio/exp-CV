#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    // Mat img = imread("../images/Lenna.png");
    Mat img = imread("../images/CH03/Fig0338(a)(blurry_moon).tif", 0);
    // Mat img = imread("../images/geral2.png", 0);

    // imshow("original", img);
    // imwrite("original.png", img);

    // {{ 0, 1, 0}, { 1,-4, 1}, { 0, 1, 0}},
    // {{ 1, 1, 1}, { 1,-8, 1}, { 1, 1, 1}},
    // {{ 0,-1, 0}, {-1, 4,-1}, { 0,-1, 0}},
    // {{-1,-1,-1}, {-1, 8,-1}, {-1,-1,-1}}

    Mat kernel[10];

    kernel[0] = (Mat_<char>(3,3) <<   /*Laplaciano - 2ª derivada*/ 
    0, 1, 0,
    1,-4, 1,
    0, 1, 0);

    kernel[1] = -kernel[0];
    // kernel[1] = (Mat_<char>(3,3) << /*negativo*/
    // 0, -1, 0,
    // -1, 4,-1,
    // 0, -1, 0);

    kernel[2] = (Mat_<char>(3,3) <<     /*diagonais*/
    1, 1, 1,
    1,-8, 1,
    1, 1, 1);

    kernel[3] = -kernel[2];
    // kernel[3] = (Mat_<char>(3,3) <<  /*negativo*/
    // -1,-1,-1,
    // -1, 8,-1,
    // -1,-1,-1);

    kernel[4] = (Mat_<char>(3,3) <<     /*Sobel X*/
    -1,-2,-1,
    0, 0, 0,
    1, 2, 1);

    kernel[5] = (Mat_<char>(3,3) <<     /*Sobel Y*/
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1);

    kernel[6] = (Mat_<char>(3,3) <<     /*Prewitt? vertical*/
    -1,-1,-1,
    0, 0, 0,
    1, 1, 1);

    kernel[7] = (Mat_<char>(3,3) <<     /*Prewitt? horizontal*/
    -1, 0, 1,
    -1, 0, 1,
    -1, 0, 1);

    kernel[8] = (Mat_<char>(3,3) <<     /*Scharr X ?*/
    -3, 0, 3,
    -10,0,10,
    -3, 0, 3);

    kernel[9] = (Mat_<char>(3,3) <<     /*Scharr ?*/
    -3,-10,-3,
    0,  0, 0,
    3, 10, 3);

    Mat result;
    // int i = 9;
    // for (int i = 0; i < 4; ++i){
    // filter2D(img, result, img.depth(), -kernel[i]);
    // imshow("filtro2D[" + to_string(i) + "]", result);
    // imshow("img - filtro2D[" + to_string(i) + "]", img - result);    
    // imshow("img + filtro2D[" + to_string(i) + "]", img + result);    

        // imwrite("filtro2D[" + to_string(i) + "].png", result);
        // imwrite("img-filtro2D[" + to_string(i) + "].png", img - result);    
        // imwrite("img+filtro2D[" + to_string(i) + "].png", img + result);
    // }

    // blur(img, img, Size(3, 3));
    Laplacian(img, result, CV_16S, 7);
    // Laplacian(img, result, img.depth(), 7);
    // convertScaleAbs(result, result);
    imshow("Laplacian", result);


    waitKey();

    return 0;
}