#include <cv.h>
#include <highgui.h>

using namespace cv;

int main(void){
    
    float zoom = .5; // reduz a imagem à metade do tamanho

    Mat pb, img = imread("../images/clock.jpg");

    cvtColor(img, pb, CV_RGB2GRAY);

    resize(img, img, Size(), zoom, zoom); // padrao: bilinear

    // vizinho mais proximo, bilinear, bicubica, por area, Lanczos
    string interName[] = {"INTER_NEAREST", "INTER_LINEAR", "INTER_CUBIC", "INTER_AREA", "INTER_LANCZOS4"};

    zoom = 2; // retorna ao tamanho original

    for(int i = 0; i < sizeof(interName)/sizeof(*interName); i++){ // = 5
        Mat interImg;
        resize(img, interImg, Size(), zoom, zoom, i);

        imshow(interName[i], interImg);
        imwrite(interName[i] + ".jpg", interImg);

        cvtColor(interImg, interImg, CV_RGB2GRAY);

        imshow("origiPB-" + interName[i], pb - interImg);
        imwrite("origiPB-" + interName[i] + ".jpg", pb - interImg);

        // imshow("origiPB-" + interName[i], Scalar(255) - pb - interImg);
        // imwrite("origiPB-" + interName[i] + ".jpg", Scalar(255) - pb - interImg);
    }

    waitKey();

    //system("nemo . &"); // abre o diretorio

    return 0;
}