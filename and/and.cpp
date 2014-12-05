#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(void){
    //Mat img = imread("../images/dollar.jpg"); // BW
    Mat img = imread("../images/CH03/Fig0314(a)(100-dollars).tif"); // BW

    cvtColor(img, img, CV_RGB2GRAY);
    equalizeHist(img, img);
    
    imwrite("ORIGINAL.jpg", img);

    string ones[8] = {"01111111", "10111111", "11011111", "11101111", "11110111", "11111011", "11111101", "11111110"};
    string zeros[8] = {"10000000", "01000000", "00100000", "00010000", "00001000", "00000100", "00000010", "00000001"};

    // rotate ?
    int bins[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

    int n = 0x80; // 10000000

    Mat o, z;
    
    for (int i = 0; i < 8; i++){
        Mat m;
        bitwise_and(img, (0x80 >> i), m);

        if(i){
            z -= m;
            equalizeHist(z,z);
            imshow(zeros[i-1] + "-" + zeros[i], z);
        }
        z = m;
        equalizeHist(m, m);
        imwrite(zeros[i] + ".jpg", m);

        bitwise_and(img, bins[i], m);

        if(i){
            o -= m;
            equalizeHist(o,o);
            imshow(ones[i-1] + "-" + ones[i], o);
        }
        o = m;
        equalizeHist(m, m);
        imwrite(ones[i] + ".jpg", m);
    }

    waitKey();

    //system("nemo . &");

    return 0;
}
