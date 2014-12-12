#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout <<
    "\nThis program demonstrates Laplace point/edge detection using OpenCV function Laplacian()\n"
    "It captures from the camera of your choice: 0, 1, ... default 0\n"
    "Call:\n"
    "./laplace [camera #, default 0]\n" << endl;
}

enum {GAUSSIAN, BLUR, MEDIAN};

// int sigma = 3;
int sigma = 3, size = 3, limiar = 100, lsize = 3;
int smoothType = GAUSSIAN;

int main( int argc, char** argv )
{
    VideoCapture cap;
    help();

    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        cap.open(argc == 2 ? argv[1][0] - '0' : 0);
    else if( argc >= 2 )
    {
        cap.open(argv[1]);
        if( cap.isOpened() )
            cout << "Video " << argv[1] <<
        ": width=" << cap.get(CAP_PROP_FRAME_WIDTH) <<
        ", height=" << cap.get(CAP_PROP_FRAME_HEIGHT) <<
        ", nframes=" << cap.get(CAP_PROP_FRAME_COUNT) << endl;
        if( argc > 2 && isdigit(argv[2][0]) )
        {
            int pos;
            sscanf(argv[2], "%d", &pos);
            cout << "seeking to frame #" << pos << endl;
            cap.set(CAP_PROP_POS_FRAMES, pos);
        }
    }

    if( !cap.isOpened() )
    {
        cout << "Could not initialize capturing...\n";
        return -1;
    }

    namedWindow( "Laplaciano convertido", 0 );
    // createTrackbar( "Sigma", "Laplacian", &sigma, 15, 0 );
    createTrackbar( "Sigma (-1)", "Laplaciano convertido", &sigma, 15, 0 );
    createTrackbar( "smoothType", "Laplaciano convertido", &smoothType, 2, 0 );
    createTrackbar( "ksize (m, m)", "Laplaciano convertido", &size, 15, 0 );
    createTrackbar( "lsize", "Laplaciano convertido", &lsize, 15, 0 );
    createTrackbar( "limiar (%)", "Laplaciano convertido", &limiar, 100, 0 );

    Mat smoothed, laplace, result;

    for(;;)
    {
        Mat frame;
        cap >> frame;

        if( frame.empty() )
            break;

        // cvtColor(frame, frame, COLOR_RGB2GRAY);

        // int ksize = (sigma*5)|1;
        int ksize = (size)|1;
        // cout << ksize << endl;
        if(smoothType == GAUSSIAN)
            // GaussianBlur(frame, smoothed, Size(ksize, ksize), sigma, sigma);
            GaussianBlur(frame, smoothed, Size(ksize, ksize), sigma -1, sigma -1);
        else if(smoothType == BLUR)
            blur(frame, smoothed, Size(ksize, ksize));
        else
            medianBlur(frame, smoothed, ksize);

        imshow("smoothed", smoothed);

        // Laplacian(smoothed, laplace, CV_16S, 5);
        Laplacian(smoothed, laplace, CV_16S, lsize|1);
        imshow("Laplaciano", laplace);
        // convertScaleAbs(laplace, result, (sigma+1)*0.25);
        convertScaleAbs(laplace, result, limiar/100.0);
        
        imshow("Laplaciano convertido", result);

        char c = (char) waitKey(30);
        // if( c == ' ' )
            // smoothType = smoothType == GAUSSIAN ? BLUR : smoothType == BLUR ? MEDIAN : GAUSSIAN;
        if( c == 'q' || c == 'Q' || (c & 255) == 27 )
            break;
    }

    return 0;
}