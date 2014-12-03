#include <cv.h>
#include <highgui.h>
// #include <iostream>

using namespace cv;
// using namespace std;

int main(void){
    
    int plano[8] = {1, 1, 1, 1, 0, 0, 0, 0};
    string zeros[8] = {"10000000", "01000000", "00100000", "00010000", "00001000", "00000100", "00000010", "00000001"};

    Mat result, neg, img = imread("../images/CH01/Fig0115(b)(100-dollars).tif", 0);
    resize(img, img, Size(), 0.65, 0.65); // padrao: bilinear
    // equalizeHist(img, img);
    imshow("img", img);
    imwrite("img.jpg", img);

    img.copyTo(result);

    result = Scalar(0);

    // cout << "img: " << img.channels() << "," << img.type() << endl;
    // cout << "res: " << result.channels() << "," << result.type() << endl;

    string res = "result:_";

    for(int i = 0; i < 8; i++){
        Mat m = img & (0x80 >> i);

        if(plano[i]){
            result += m;
            res += "1";
        } else{
            res += "0";
        }

        threshold(m, m, 0, 255, THRESH_BINARY);
        // imshow(zeros[i], m);
        imwrite(zeros[i] + ".jpg", m);
    }

    imshow(res, result);
    imwrite(res + ".jpg", result);

    waitKey();

    return 0;
}