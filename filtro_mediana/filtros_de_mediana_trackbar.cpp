#include <cv.h>
#include <highgui.h>
#include <string>

using namespace cv;
using namespace std;

Mat img, filtro;
int mn; // tamanho de m e n (quadrado)

void filtragem(int, void *){

    // impar e positivo
    mn |= 1;

    medianBlur(img, filtro, mn);

    // for (int i = 0; i < 10; ++i){
    //     medianBlur(filtro, filtro, mn);
    // }
    
    imshow("filtro de mediana", filtro);

    // Mat sub = img - filtro;
    // imshow("img - filtro", sub);
}

int main(void){

    // img = imread("../images/Lenna.png");
    // img = imread("../images/CH03/Fig0333(a)(test_pattern_blurring_orig).tif", 0);
    img = imread("../images/CH03/Fig0335(a)(ckt_board_saltpep_prob_pt05).tif", 0);

    // imwrite("original.png", img);

    namedWindow("filtro de mediana", WINDOW_AUTOSIZE);
    // namedWindow("img - filtro", WINDOW_AUTOSIZE);

    createTrackbar("m, n: ", "filtro de mediana", &mn, 35, filtragem);
    // createTrackbar("m, n: ", "filtro de mediana", &mn, img.cols, filtragem);
    filtragem(mn, 0);

    char c;
    do{
        c = (char) cvWaitKey();
        if (c == 's' || c == 'S') imwrite("m" + to_string(mn) + ".png", filtro); // salva a imagem
    }while(c != 27); // ESC

    return 0;
}