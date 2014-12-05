#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

#define QTDEBITS 4 // MSB: min 1, máx 4

int main(void){
    Mat neg, img = imread("../images/Lenna.png");
    // resize(img, img, Size(), 0.15, 0.15);
    imshow("original", img);
    imwrite("original.png", img);

    // planos BGR para a img e para o negativo
    vector<Mat> bgr, bgr_neg;
    
    // distribui as camadas nos planos
    split(img, bgr);
    // extrai o negativo
    split(Scalar(255, 255, 255) - img, bgr_neg); // extrai o negativo

    // mescla as camadas
    merge(bgr_neg, neg);

    imshow("negativo", neg);
    imwrite("negativo.png", neg);

    // zera a imagem e cria 3 planos com as mesmas características da img
    img = Scalar(0);
    vector<Mat> result_plan;
    split(img, result_plan);

    for (int i = 0; i < QTDEBITS; i++){ // para os bits do MSB
        for (int j = 0; j < result_plan.size(); j++){ // para cada camada BGR
            result_plan[j] += bgr[j] & (0x80 >> i); // img no MSB
            result_plan[j] += (bgr_neg[j] & (0x80 >> i)) / 16; // negativo no LSB 
        }
    }

    // mescla os planos
    merge(result_plan, img);

    imshow("soma", img);
    imwrite("soma.png", img);

    // split(img, result_plan);

    // recuperação das imagens
    for (int i = 0; i < result_plan.size(); i++){
        bgr[i] = (result_plan[i] & 0xF0); // zera o LSB
        bgr_neg[i] = (result_plan[i] & 0x0F) * 16; // zera o MSB e rotaciona o LSB -> MSB
        //bgr_neg[i] = 255 - (result_plan[i] & 0x0F) * 16;
    }

    // mescla os planos
    merge(bgr, img);
    merge(bgr_neg, neg);

    imshow("original rec", img);
    imwrite("original_rec.png", img);
    
    imshow("negativo rec", neg);
    imwrite("negativo_rec.png", neg);

    waitKey();

    return 0;
}