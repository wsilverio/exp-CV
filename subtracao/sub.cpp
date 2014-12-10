#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat bit0, bit1, img = imread("../images/CH02/Fig0221(a)(ctskull-256).tif"); // BW
    cvtColor(img, img, CV_RGB2GRAY);
    equalizeHist(img, img);
    //resize(img, img, Size(), 0.65, 0.65); // padrao: bilinear

    // imshow("origi", img);
    imwrite("origi.jpg", img);
    // double minVal, maxVal;
    // minMaxLoc(bit0, &minVal, &maxVal);
    // cout << minVal << endl << maxVal << endl;

    string ones[8] = {"01111111", "10111111", "11011111", "11101111", "11110111", "11111011", "11111101", "11111110"};
    string zeros[8] = {"10000000", "01000000", "00100000", "00010000", "00001000", "00000100", "00000010", "00000001"};
    int bin[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

    int n = 0x80;

    for (int i = 0; i < 8; i++){

        bitwise_and(img, (0x80 >> i), bit0);
        //bit0 = img - (img & bin[i]);

        bit0 = img - bit0;

        //minMaxLoc(bit0, &minVal, &maxVal);
        //cout << minVal << endl << maxVal << endl;

        // threshold(bit0, bit0, maxVal - 1, 255, THRESH_BINARY);
        // equalizeHist(bit0, bit0);
        // imshow(ones[i], bit0);
        imwrite(ones[i]+".jpg", bit0);

        bitwise_and(img, bin[i], bit1);
        bit1 = img - bit1;
        // equalizeHist(bit1, bit1);
        imwrite(zeros[i]+".jpg", bit1);
    }

    waitKey();

    return 0;
}