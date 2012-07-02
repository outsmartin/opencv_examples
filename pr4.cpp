#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
  VideoCapture cap("pr4.avi");
  if(!cap.isOpened())  // check if we succeeded
    throw "bla";

  Mat edges, frame;
  cap >> frame;
  VideoWriter vwrite("pr4_output.avi", -1, 25, Size(frame.cols, frame.rows));
  namedWindow("edges",1);
  namedWindow("org",1);
  for(;;)
  {
    if(cap.get(CV_CAP_PROP_POS_AVI_RATIO) > .95) // if video ends ...
      break;
    //cap.set(CV_CAP_PROP_POS_MSEC, 0); // ... restart video

    cap >> frame; // get a new frame from camera
    cvtColor(frame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    Canny(edges, edges, 60, 120, 3);
    imshow("edges", edges);
    imshow("org", frame);
    vwrite.write(edges);
    if(waitKey(30) >= 0)
      break;
  }
  // Free the resources.
  //waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
