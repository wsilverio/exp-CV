#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(void){
    
    float zoom = .5; // reduz a imagem à metade do tamanho

    Mat img = imread("../images/clock.jpg");
    resize(img, img, Size(), zoom, zoom); // padrao: bilinear

    Mat vmp, bilin, bicub, area, lanc; // vizinho mais proximo, bilinear, bicubica, por area, Lanczos
    
    string interName[] = {"INTER_NEAREST", "INTER_LINEAR", "INTER_CUBIC", "INTER_AREA", "INTER_LANCZOS4"};

    vector<Mat> interImg(sizeof(interName)/sizeof(*interName)); // = 5

    zoom = 2; // retorna ao tamanho original

    //imshow("ORIGINAL", img);

    for(int i = 0; i < interImg.size(); i++){
        resize(img, interImg[i], Size(), zoom, zoom, i);
        imwrite(interName[i] + ".jpg", interImg[i]);
        //imshow(interName[i], interImg[i]);
    }

    //waitKey();

    //system("nemo . &"); // abre o diretorio

    return 0;
}