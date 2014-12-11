// http://docs.opencv.org/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html#histogram-calculation

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(void){

  // fonte, destino
  Mat src, dst;

  // carrega a imagem fonte
  src = imread("../images/Lenna.png");

  // exibe a imagem
  //imshow("src", src);
  imwrite("src.png", src);

  //if(!src.data) return -1; // argc, *argv[]

  // separa a imagem nas 3 camadas (B, G e R)
  vector<Mat> bgr_planes;
  split(src, bgr_planes);

  // negativo
  
  Mat neg = 255 - bgr_planes[0]; // p/ azul
  //imshow("negativo", neg);
  
  imwrite("neg.png",neg);

  // exibe as tres camadas
  
  for (int i = 0; i < bgr_planes.size(); ++i){
    string s[] = {"B", "G", "R"};
    // imshow(s[i], bgr_planes[i]);
    imwrite(s[i] + ".png", bgr_planes[i]);
  }
  
  
  // estabelece a qtde de passos do histograma
  int histSize = 256; // exclusivo

  // limites do (B,G,R)
  float range[] = {0, 256} ;
  const float* histRange = {range};

  bool uniform = true; bool accumulate = false;

  // uma imagem para cada camada
  Mat b_hist, g_hist, r_hist;

  // (para cada) Gera uma imagem de 1 coluna com o histograma em valores de cinza (0 - 255)
  calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
  calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
  calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

  // imshow("hB", b_hist);
  // imshow("hG", g_hist);
  // imshow("hR", r_hist);
  imwrite("hB.png", b_hist);
  imwrite("hG.png", g_hist);
  imwrite("hR.png", r_hist);

  // largura, altura, intervalo entre os passos
  int hist_w = 512, hist_h = 400, bin_w = cvRound((double) hist_w/histSize);

  // imagem 8 bits, 3 camadas, bg 000
  Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

  // Normaliza o histograma [0, histImage.rows]
  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
  normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
  normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

  // imshow("nB", b_hist);
  // imshow("nG", g_hist);
  // imshow("nR", r_hist);
  imwrite("nB.png", b_hist);
  imwrite("nG.png", g_hist);
  imwrite("nR.png", r_hist);

  // Draw for each channel
  for(int i = 1; i < histSize; i++){
    line(histImage, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
     Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
     Scalar(255, 0, 0), 2, 8, 0);

    line(histImage, Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
     Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
     Scalar(0, 255, 0), 2, 8, 0);

    line(histImage, Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
     Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
     Scalar(0, 0, 255), 2, 8, 0);
  }

  namedWindow("Histo", CV_WINDOW_AUTOSIZE);
  imshow("Histo", histImage);

  imwrite("Histo.png", histImage);

  waitKey(0);

  return 0;
}