#include <cv.h>
#include <highgui.h>

using namespace cv;

int main (void){
    
     /*
     cout << CV_LOAD_IMAGE_ANYDEPTH << endl; // 2
     cout << CV_LOAD_IMAGE_COLOR << endl; // 1
     cout << CV_LOAD_IMAGE_GRAYSCALE << endl; // 0
    */

    Mat imgC, imgG;
    imgC = imread("../images/Lenna.png");

    cvtColor(imgC, imgG, CV_RGB2GRAY);

    //namedWindow("cor", CV_WINDOW_AUTOSIZE );
    //namedWindow("cinza", CV_WINDOW_AUTOSIZE );

    imshow("cor", imgC);
    imshow("cinza", imgG);

    imwrite("cor.png", imgC);
    imwrite("cinza.png", imgG);
    
    waitKey();

  return 0;
}
