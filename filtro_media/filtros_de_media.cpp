#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat img = imread("../images/Lenna.png");

    imshow("original", img);
    imwrite("original.png", img);

    Mat kernel = (Mat_<float>(3,3) <<    
        1, 2, 1,
        2, 4, 2,
        1, 2, 1); // soma = 16

    // float sum = 0;
    // for (int i = 0; i < kernel.rows; ++i){
    //     for (int j = 0; j < kernel.cols; ++j){
    //         sum += kernel.at<float>(i, j);   
    //     }
    // }
    // cout << sum << endl << endl;
    // kernel /= sum;
    kernel /= 16.;
    // for (int i = 0; i < kernel.rows; ++i){
    //     for (int j = 0; j < kernel.cols; ++j){
    //         cout << kernel.at<float>(i, j) << " ";
    //     }
    //     cout << endl;
    // }    

    Mat result;
    filter2D(img, result, img.depth(), kernel);

    imshow("filtro2D ponderado", result);
    imshow("img - filtro2D ponderado", img - result);

    imwrite("filtro2D_ponderado.png", result);
    imwrite("img_-_filtro2D_ponderado.png", img - result);

    for (int i = 0, m[] = {3, 5, 9, 15, 35, 75, 105, (img.cols%2)?img.cols:img.cols-1}; i < sizeof(m)/sizeof(int); ++i){
        // blur(img, result, Size(m[i], m[i]), Point(-1,-1), BORDER_DEFAULT);
        blur(img, result, Size(m[i], m[i]));

        imshow("blur " + to_string(m[i]) + "x" + to_string(m[i]), result);
        imwrite("blur" + to_string(m[i]) + "x" + to_string(m[i]) + ".png", result);

        imshow("img - blur" + to_string(m[i]) + "x" + to_string(m[i]), img - result);
        imwrite("img_-_blur" + to_string(m[i]) + "x" + to_string(m[i]) + ".png", img - result);
    }

    // img = imread("../images/CH03/Fig0333(a)(test_pattern_blurring_orig).tif");
    // imshow("placa_original", img);
    // imwrite("placa_original.png", img);

    // blur(img, result, Size(3, 3));

    // imshow("blur_Placa 3x3", result);
    // imwrite("blur_Placa_3x3.png", result);

    // imshow("img - blur_Placa 3x3", img - result);
    // imwrite("img_-_blur_Placa 3x3.png", img - result);

    waitKey();

    return 0;
}