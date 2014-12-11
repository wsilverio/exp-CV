#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <string>

using namespace cv;
using namespace std;

Mat img, filtro;
int mn; // tamanho de m e n (quadrado)
int limiar;

void limiarizacao(int, void*){
    double maxVal;
    minMaxLoc(img, NULL, &maxVal);
    Mat lim;
    threshold(filtro, lim, (maxVal*limiar/100.0), 255, THRESH_BINARY);
    imshow("limiarizacao", lim);
}

void filtragem(int, void *){

    // impar e positivo
    mn |= 1;

    blur(img, filtro, Size(mn, mn));

    Mat sub = img - filtro;

    // rectangle(filtro, Point(0, 0), Point(mn, mn), Scalar(255, 255, 255) - mean(filtro), 1, 8, 0);

    imshow("filtro de media", filtro);

    imshow("img - filtro", sub);
    // moveWindow("img - filtro", sub.cols + 30, 30);
    
    limiarizacao(limiar, 0);
}

int main(void){

    // img = imread("../images/Lenna.png");
    // img = imread("../images/CH03/Fig0333(a)(test_pattern_blurring_orig).tif");
    img = imread("../images/CH03/Fig0334(a)(hubble-original).tif");

    namedWindow("img - filtro", WINDOW_AUTOSIZE);
    namedWindow("filtro de media", WINDOW_AUTOSIZE);
    namedWindow("limiarizacao", WINDOW_AUTOSIZE);

    createTrackbar("m, n: ", "filtro de media", &mn, 35, filtragem);
    // createTrackbar("m, n: ", "filtro de media", &mn, img.cols, filtragem);
    filtragem(mn, 0);

    createTrackbar("%: ", "limiarizacao", &limiar, 100, limiarizacao);
    // limiarizacao(limiar, 0);

    waitKey();

    return 0;
}