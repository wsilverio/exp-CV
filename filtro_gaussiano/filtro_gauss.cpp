#include <cv.h>
#include <highgui.h>
#include <string>

using namespace cv;
using namespace std;

int main(void){

    // Mat img = imread("../images/Lenna.png");
    Mat img = imread("../images/circ.png");
    imshow("original", img);

    int m = 5;
    double sigma = 3;
    double k = 4.5;

    Mat filtro;

    GaussianBlur(img, filtro, Size(m, m), sigma);
    imshow("filtro gaussiano", filtro);
    imwrite("filtro_gaussiano.png", filtro);

    filtro = img - filtro;
    imshow("mascara", filtro);
    imwrite("mascara.png", filtro);

    imshow("original + " + to_string(k) + "*mascara", img + k*filtro);    
    imwrite("original+" + to_string(k) + "*mascara.png", img + k*filtro);    

    waitKey();

    return 0;
}