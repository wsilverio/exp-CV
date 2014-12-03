#include <cv.h>
#include <highgui.h>

using namespace cv;

int main (void){
    

  Mat src, dst;
  //src = imread("../images/Lenna.png", 0);

  string images[4] = {"Fig0316(1)(top_left)", "Fig0316(2)(2nd_from_top)", "Fig0316(3)(third_from_top)", "Fig0316(4)(bottom_left)"};

  for (int i = 0; i < 4; i++){
    src = imread("../images/CH03/" + images[i] + ".tif", 0);
    equalizeHist(src, dst);

    imshow(images[i] + "orig", src);
    imshow(images[i] + "equa", dst);

    imwrite(images[i] + "orig.jpg", src);
    imwrite(images[i] + "equa.jpg", dst);
  }
    
  waitKey();

  return 0;
}