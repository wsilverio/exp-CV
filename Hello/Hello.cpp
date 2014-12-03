#include <cv.h>
#include <highgui.h>
// #include <iostream>

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
    // grava as imagens
    imwrite("cor.png", imgC);
    imwrite("cinza.png", imgG);
    // aguarda qualquer tecla para fechar as janelas
    waitKey();

  return 0;
}
