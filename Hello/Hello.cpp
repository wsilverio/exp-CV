#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
// using namespace std;

int main (void){

    /*
    cout << CV_LOAD_IMAGE_ANYDEPTH << endl; // 2
    cout << CV_LOAD_IMAGE_COLOR << endl; // 1
    cout << CV_LOAD_IMAGE_GRAYSCALE << endl; // 0
    */

    Mat imgC, imgG;
    // carega a imagem em imgC (color)
    imgC = imread("../images/Lenna.png");

    // converte para a escala de cinza (gray)
    cvtColor(imgC, imgG, CV_RGB2GRAY);

    //namedWindow("cor", CV_WINDOW_AUTOSIZE );
    //namedWindow("cinza", CV_WINDOW_AUTOSIZE );

    // exibe as imagens
    imshow("cor", imgC);
    imshow("cinza", imgG);
    imshow("cor neg", Scalar(255, 255, 255) - imgC);
    imshow("cinza neg", Scalar(255) - imgG);
    imshow("cor - cor neg", imgC - (Scalar(255, 255, 255) - imgC));
    imshow("cinza - cinza neg", imgG - (Scalar(255) - imgG));
    // grava as imagens
    imwrite("cor.png", imgC);
    imwrite("cinza.png", imgG);
    imwrite("cor_neg.png", Scalar(255, 255, 255) - imgC);
    imwrite("cinza_neg.png", Scalar(255) - imgG);
    imwrite("cor_-_cor_neg.png", imgC - (Scalar(255, 255, 255) - imgC));
    imwrite("cinza_-_cinza_neg.png", imgG - (Scalar(255) - imgG));

    // aguarda qualquer tecla para fechar as janelas
    waitKey();

    return 0;
}
