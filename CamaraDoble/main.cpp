#include <ctime>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

#define CAM_WIDTH 640
#define CAM_HEIGHT 360
// #define CAM_WIDTH 320
// #define CAM_HEIGHT 180

using namespace cv;

int main(){

    VideoCapture cap[2];

    cap[0] = VideoCapture(0);
    cap[1] = VideoCapture(1);

    if(!cap[0].isOpened() || !cap[1].isOpened()){
        std::cout << "Erro ao abrir o(s) dispositivo(s) de video\n";
        return -1;
    }

    // resize
    cap[0].set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH); 
    cap[0].set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
    cap[1].set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH); 
    cap[1].set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

    cap[0].set(CV_CAP_PROP_FPS, 30);
    cap[1].set(CV_CAP_PROP_FPS, 30);

    // const char * cam[] = {"CAM 0", "CAM 1"};
    // namedWindow(cam[0], CV_WINDOW_AUTOSIZE);
    // namedWindow(cam[1], CV_WINDOW_AUTOSIZE);

    namedWindow("CamaraDoble", CV_WINDOW_AUTOSIZE);

    Mat frame[2];
    Mat doble(Size(2*CAM_WIDTH, CAM_HEIGHT), CV_8UC3);

    std::string fps;
    clock_t begin = clock();
    double fps_acum = 0.0;

    bool rotate = false;

    for(int acc = 0; ; acc++){


        cap[0] >> frame[0];
        cap[1] >> frame[1];

        if (rotate){
            // eixo X
            flip(frame[0], frame[0], 0);
            flip(frame[1], frame[1], 0);
        }else{
            // eixo Y (espelho)
            flip(frame[0], frame[0], 1);
            flip(frame[1], frame[1], 1);
        }

        frame[0].copyTo(doble(Rect((!rotate)?0:CAM_WIDTH, 0, CAM_WIDTH, CAM_HEIGHT)));
        frame[1].copyTo(doble(Rect((!rotate)?CAM_WIDTH:0, 0, CAM_WIDTH, CAM_HEIGHT)));

        if (acc < 5)   fps_acum = (CLOCKS_PER_SEC / double(clock() - begin));
        else            fps_acum = 0.99*fps_acum + 0.01*(CLOCKS_PER_SEC / double(clock() - begin));

        // fps = std::to_string(CLOCKS_PER_SEC / double(clock() - begin));
        begin = clock();

        std::cout << "fps: " << fps_acum << std::endl;

        // putText(doble, "fps: "+std::to_string(fps_acum), Point (10, 20), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0), 1, 8);
        imshow("CamaraDoble", doble);

        char c = (char) cvWaitKey(1);

        if(c == 'r' || c == 'R') rotate = !rotate;
        else if (c == 27) break; // ESC
        
    }

    destroyAllWindows();

    cap[0].release();
    cap[1].release();

    return 0;
}