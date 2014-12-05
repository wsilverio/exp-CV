#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
    Mat img, padrao;

    img = imread("../images/CH02/Fig0229(a)(tungsten_filament_shaded).tif", 0);
    padrao = imread("../images/CH02/Fig0229(b)(tungsten_sensor_shading).tif", 0);

    // cout << img.size() << endl << padrao.size();
    
    if(img.size() != padrao.size()){
        cout << "\n***As imagens devem ter o mesmo tamanho.***\n";
        return 1;
    }

    Mat res(img.size(), img.type());
    
    // divide(img, padrao, res); // ?

    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
            res.at<uchar>(i, j) = img.at<uchar>(i, j) / (padrao.at<uchar>(i, j) / 255.0);
        }
    }

    imshow("img", img);
    imwrite("original.jpg", img);
    imshow("res", res);
    imwrite("res.jpg", res);

    waitKey();

    return 0;
}