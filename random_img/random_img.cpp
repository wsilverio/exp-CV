#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat img(Size(800, 500), CV_8UC1);
    
    int med = 100; // media
    int dp = 5; // desvio padrao

    randu(img, med - dp*dp, med + dp*dp);
    imshow("randu", img);
    imwrite("randu.jpg", img);

    for (int i = 0; i < 16; ++i){
        Mat mat;
        blur(img, mat, Size(i+1, i+1), Point(-1,-1), BORDER_DEFAULT);
        imshow(to_string(i+1), mat);
    }

    cout << "media:     " << med << ", desvio padrao: " << dp << endl;

    double vmin, vmax;
    minMaxLoc(img, &vmin, &vmax);
    cout << "randu(min): " << vmin << ", randu(max): " << vmax << endl;

    randn(img, med, dp);
    imshow("randn", img);
    imwrite("randn.jpg", img);

    minMaxLoc(img, &vmin, &vmax);
    cout << "randn(min): " << vmin << ", randn(max): " << vmax << endl; 

    img = imread("../images/Lenna.png", 0);

    Mat res = img.clone();

    float fator = 0.25;

    randShuffle(img, fator);
    imshow("randShuffle", img);
    imwrite("randShuffle.jpg", img);

    randShuffle(img, 50*fator);
    imshow("img_-_*randShufflex*", res - img);
    imwrite("img_-_randShufflex.jpg", res - img);

    waitKey();
    return 0;
}