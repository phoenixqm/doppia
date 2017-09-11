
#include <cstdlib>
#include <iostream>

#include <boost/scoped_ptr.hpp>


#include "PedDetectionApplication.hpp"

#include "opencv2/opencv.hpp"

using namespace std;

int testOpenCV_video(int, char**)
{
    // VideoCapture cap(0); // open the default camera
    cv::VideoCapture cap(std::string("airport1.mp4")); // open video file

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::Mat edges;
    cv::namedWindow("edges",1);

    for(;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        cv::cvtColor(frame, edges, CV_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
        if(cv::waitKey(30) >= 0) 
            break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}



// -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
int main(int argc, char *argv[])
{
    // testOpenCV_video(argc, argv);

    int ret = EXIT_SUCCESS;

    try
    {
        boost::scoped_ptr<doppia::PedDetectionApplication>
        application_p( new doppia::PedDetectionApplication() );

        ret = application_p->main(argc, argv);
    }
    // on linux re-throw the exception in order to get the information
    catch (std::exception & e)
    {
        cout << "\033[1;31mA std::exception was raised:\033[0m " << e.what () << endl;
        ret = EXIT_FAILURE; // an error appeared
        throw;
    }
    catch (...)
    {
        cout << "\033[1;31mAn unknown exception was raised\033[0m " << endl;
        ret = EXIT_FAILURE; // an error appeared
        throw;
    }

    return ret;
}


