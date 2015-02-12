 // g++ main_thread.cpp -o thcameradoble.run `pkg-config --cflags --libs opencv` -lboost_thread -lboost_system -std=c++11 -lX11

// libv4l2: error dequeuing buf: Invalid argument
// VIDIOC_DQBUF: Invalid argument
// libv4l2: error dequeuing buf: Invalid argument
// VIDIOC_DQBUF: Invalid argument
// libv4l2: error querying buffer 1: Bad file descriptor
// Segmentation fault
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
// #include <thread>  
#include <X11/Xlib.h>
// #include <mutex>  
#include <boost/thread/thread.hpp>

// #define CAM_WIDTH 640
// #define CAM_HEIGHT 360
#define CAM_WIDTH 320
#define CAM_HEIGHT 180

using namespace cv;

// std::mutex mtx0;
// std::mutex mtx1;
boost::mutex mtx0;
boost::mutex mtx1;

void camZero(VideoCapture *cap, Mat &frame){
    double fps_acum = 0.0;
    clock_t begin = clock();

    for(int acc;;acc++){
        mtx0.lock();
        (*cap) >> (frame);
        mtx0.unlock();

        if (acc < 5)   fps_acum = (CLOCKS_PER_SEC / double(clock() - begin));
        else            fps_acum = 0.99*fps_acum + 0.01*(CLOCKS_PER_SEC / double(clock() - begin));
        begin = clock();
        std::cout << "FPS0: " << fps_acum << std::endl;
    }
}

void camUm(VideoCapture *cap, Mat &frame){
    double fps_acum = 0.0;
    clock_t begin = clock();

    for(int acc;;acc++){
        mtx1.lock();
        (*cap) >> (frame);
        mtx1.unlock();

        if (acc < 5)   fps_acum = (CLOCKS_PER_SEC / double(clock() - begin));
        else            fps_acum = 0.99*fps_acum + 0.01*(CLOCKS_PER_SEC / double(clock() - begin));
        begin = clock();
        std::cout << "FPS1: " << fps_acum << std::endl;
    }
}

/*void camZero(){
    namedWindow("CAM 0", CV_WINDOW_AUTOSIZE);
    VideoCapture cap(0);
    Mat frame;
    for(;;){
        cap >> frame;
        imshow("CAM 0", frame);
        char c = (char) cvWaitKey(30);
        if (c == 27) break;
    }
    destroyWindow("CAM 0");
    cap.release();
}

void camUm(){
    namedWindow("CAM 1", CV_WINDOW_AUTOSIZE);
    VideoCapture cap(1);
    Mat frame;
    for(;;){
        cap >> frame;
        imshow("CAM 1", frame);
        char c = (char) cvWaitKey(30);
        if (c == 27) break;
    }
    destroyWindow("CAM 1");
    cap.release();
}*/

int main(){

    // XInitThreads();

    VideoCapture cap[2];
    cap[0] = VideoCapture(0);
    cap[1] = VideoCapture(1);

    if(!cap[0].isOpened() || !cap[1].isOpened()){
        std::cout << "Erro ao abrir o(s) dispositivo(s) de video\n";
        return -1;
    }

    cap[0].set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH); cap[0].set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
    cap[1].set(CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH); cap[1].set(CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

    Mat frame[2];

    cap[0] >> frame[0];
    cap[1] >> frame[1];

    // std::thread thZero  (camZero, std::ref(cap[0]), std::ref(frame[0]));
    // std::thread thUm    (camUm,   std::ref(cap[1]), std::ref(frame[1]));

    boost::thread thZero(camZero,   &cap[0], std::ref(frame[0]));
    boost::thread thUm  (camUm,     &cap[1], std::ref(frame[1]));

    // boost::thread thZero(camZero);
    // boost::thread thUm  (camUm);

    // thZero.join();
    // thUm.join();

    namedWindow("CAM 0", CV_WINDOW_AUTOSIZE);
    namedWindow("CAM 1", CV_WINDOW_AUTOSIZE);

    Display *display = XOpenDisplay(NULL);
    Screen  *screen = DefaultScreenOfDisplay(display);
    const int S_WIDTH  = screen->width;
    const int S_HEIGHT = screen->height;

    // moveWindow("CAM 0", (S_WIDTH-2*CAM_WIDTH)/2, S_HEIGHT/2);
    // moveWindow("CAM 1", (S_WIDTH-2*CAM_WIDTH)/2+CAM_WIDTH, S_HEIGHT/2);

    bool rotate = false;

    for(;;){

        if (rotate){
            // eixo X
            flip(frame[0], frame[0], 0);
            flip(frame[1], frame[1], 0);
        // }else{
        //     // eixo Y (espelho)
        //     flip(frame[0], frame[0], 1);
        //     flip(frame[1], frame[1], 1);
        // }
        }

        imshow("CAM 0", frame[0]);
        imshow("CAM 1", frame[1]);

        char c = (char) cvWaitKey(30);
        // if(c == 'r' || c == 'R') rotate = !rotate;
        // else
         if (c == 27) break; // ESC
    }

    // cvWaitKey();

    destroyAllWindows();

    cap[0].release();
    cap[1].release();

    return 0;
}