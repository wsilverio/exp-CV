#include <cv.h>
#include <highgui.h>
#include <string>

using namespace cv;
using namespace std;

Mat img;
int mn; // tamanho de m e n (quadrado)

void filtragem(int, void *){

    // impar e positivo
    mn = (mn%2)?(mn):(mn+1);

    Mat filtro;

    medianBlur(img, filtro, mn);

    imshow("filtro de mediana", filtro);

    // Mat sub = img - filtro;
    // imshow("img - filtro", sub);
}

int main(void){

    // img = imread("../images/Lenna.png");
    // img = imread("../images/CH03/Fig0333(a)(test_pattern_blurring_orig).tif", 0);
    img = imread("../images/CH03/Fig0335(a)(ckt_board_saltpep_prob_pt05).tif", 0);

    namedWindow("filtro de mediana", WINDOW_AUTOSIZE);
    // namedWindow("img - filtro", WINDOW_AUTOSIZE);

    createTrackbar("m, n: ", "filtro de mediana", &mn, 35, filtragem);
    // createTrackbar("m, n: ", "filtro de mediana", &mn, img.cols, filtragem);
    filtragem(mn, 0);

    waitKey();

    return 0;
}