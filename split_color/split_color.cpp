#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

int main(void){
	Mat img = imread("../images/Lenna.png");
	imshow("img", img);
	imwrite("img.png", img);

	// cria as imagens para cada camada
	vector<Mat> B_vec, G_vec, R_vec;

	// separa a img nas camadas
	split(img, B_vec);
	split(img, G_vec);
	split(img, R_vec);

	// indices [B][G][R]
	int b = 0, g = 1, r = 2;

	// zera as camadas não selecionadas
	for (int i = 0; i < 3; i++){
		if(i != b) B_vec[i].setTo(0);
		if(i != g) G_vec[i].setTo(0);
		if(i != r) R_vec[i].setTo(0);
	}

	Mat B, G, R;

	// float fator = 1000;
	
	merge(B_vec, B);
	// randShuffle(B, fator);	
    imshow("B", B);
    imwrite("B.png", B);
	
	merge(G_vec, G);
	// randShuffle(G, fator);
    imshow("G", G);
    imwrite("G.png", G);

    merge(R_vec, R);
    // randShuffle(R, fator);
    imshow("R", R);
    imwrite("R.png", R);

	imshow("B neg", Scalar(255, 0, 0) - B);
	imshow("G neg", Scalar(0, 255, 0) - G);
	imshow("R neg", Scalar(0, 0, 255) - R);
	imwrite("B_neg.png", Scalar(255, 0, 0) - B);
	imwrite("G_neg.png", Scalar(0, 255, 0) - G);
	imwrite("R_neg.png", Scalar(0, 0, 255) - R);

	imshow("img - B", img - B);
	imshow("img - G", img - G);
	imshow("img - R", img - R);
	imwrite("img-B.png", img - B);
	imwrite("img-G.png", img - G);
	imwrite("img-R.png", img - R);

	imshow("(B, 255, 255)", Scalar(0, 255, 255) + B);
	imshow("(255, G, 255)", Scalar(255, 0, 255) + G);
	imshow("(255, 255, R)", Scalar(255, 255, 0) + R);
	imwrite("(B,255,255).png", Scalar(0, 255, 255) + B);
	imwrite("(255,G,255).png", Scalar(255, 0, 255) + G);
	imwrite("(255,255,R).png", Scalar(255, 255, 0) + R);

	waitKey();
	
	return 0;
}