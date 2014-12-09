#include <cv.h>
#include <highgui.h>
#include <string>

using namespace cv;
using namespace std;

int main(void){

    // Mat img = imread("../images/Lenna.png");
    Mat img = imread("../images/CH03/Fig0340(a)(dipxe_text).tif");
    imshow("original", img);

    int m = 5;
    double sigma = 3;
    double k = 4.5;

    Mat filtro;

    GaussianBlur(img, filtro, Size(m, m), sigma);
    imshow("filtro gaussiano", filtro);

    filtro = img - filtro;
    imshow("mascara", filtro);

    imshow("resultado", img + k*filtro);    

    waitKey();

    return 0;
}