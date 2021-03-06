#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){

    VideoCapture cap(0);

    if(!cap.isOpened())
        return -1;

    Mat atual, anterior;
    cap >> anterior;
    cvtColor(anterior, anterior, CV_BGR2GRAY);

    namedWindow("video", CV_WINDOW_AUTOSIZE);

    while(1) {
        Mat atual;
        cap >> atual;

        cvtColor(atual, atual, COLOR_RGB2GRAY);

        Mat dif = atual - anterior;
        anterior = atual.clone();

        GaussianBlur(dif, dif, Size(7,7), 1.5, 1.5);
        Canny(dif, dif, 0, 30, 3);
        imshow("video", dif);

        // if(waitKey(30) >= 0) break;
        char c = (char) cvWaitKey(30);
        if (c == 's' || c == 'S') imwrite(to_string(rand()) + ".png", dif); // salva a imagem
        else if(c == 27) break;

    }

    return 0;
}