#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

#define QTDEBITS 4 // min 1, máx 4

int main(void){

    Mat neg, img = imread("../images/CH01/Fig0115(b)(100-dollars).tif", 0);
    // resize(img, img, Size(), 0.25, 0.25);
    
    imshow("original", img);
    imwrite("original.png", img);

    neg = 255 - img;
    // imshow("negativo", neg);
    imwrite("negativo.png", neg);

    // result com o mesmo tipo e numero de canais que img
    Mat result(Mat::zeros(img.size(), img.type()));

    for (int i = 0; i < QTDEBITS; i++){ // captura QTDEBITS do MSB 
        result += img & (0x80 >> i); // resultMSB = imgMSB
        result += (neg & (0x80 >> i)) / 16; // resultLSB = negMSB // ### (/16 = >> 4) ###
    }

    imshow("soma", result);
    imshow("original rec", result & 0xF0);
    imshow("negativo rec", (result & 0x0F) * 16); // ### (*16 = << 4) ###

    imwrite("soma.png", result);
    imwrite("original_rec.png", result & 0xF0); // recupera o MSB
    imwrite("negativo_rec.png", (result & 0x0F) * 16); // recupera o MSB // ### (*16 = << 4) ###



    waitKey();

    return 0;
}
