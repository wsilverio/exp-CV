#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat imagem = imread("../images/CH03/Fig0343(a)(skeleton_orig).tif", 0);

    imshow("imagem", imagem);
    imwrite("img.png", imagem);

    Mat kernel = (Mat_<char>(3,3) <<
        -1,-1,-1,
        -1, 8,-1,
        -1,-1,-1 );

    Mat result, lapla;
    filter2D(imagem, lapla, CV_16S, kernel); // diag neg
    // Laplacian(imagem, lapla, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(lapla, lapla);
    imshow("Laplaciano Diagonal Negativo", lapla);
    imwrite("LDN.png", lapla);
    add(imagem, lapla, result);
    imshow("imagem + LDN", result);
    imwrite("img+LDN.png", result);

    Mat sobelX, sobelY;
    Sobel(imagem, sobelX, CV_16S, 1, 0); // k = 3
    convertScaleAbs(sobelX, sobelX);
    Sobel(imagem, sobelY, CV_16S, 0, 1); // k = 3
    convertScaleAbs(sobelY, sobelY);

    add(sobelX, sobelY, result);
    imshow("Sobel", result);
    imwrite("Sobel.png", result);

    blur(result, result, Size(5, 5));
    imshow("Media(sobel) 5x5", result);
    imwrite("Media(sobel)5x5.png", result);

    multiply(result, lapla, result, 1./255);
    imshow("mascara: media * laplaciano", result);
    imwrite("mascara_media*laplaciano.png", result);

    add(imagem, result, result);
    imshow("imagem + mascara", result);
    imwrite("imagem+mascara.png", result);

    for (int i = 0; i < result.rows; ++i){
        for (int j = 0; j < result.cols; ++j){
            result.at<uchar>(i, j) = 255*std::pow(result.at<uchar>(i, j)/255., 0.5);
        }
    }

    imshow("correcao de gama (0.5)", result);
    imwrite("correcao_gama.png", result);

    waitKey();

    return 0;
}