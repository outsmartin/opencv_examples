#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
int main ()
{
  using namespace cv;
  // Open the file.
  Mat orig;
  orig = imread("./bin/media/pr2.jpg");

  Mat blue( orig.rows, orig.cols, CV_8UC3, Scalar(0,0,0) );
  Mat red( orig.rows, orig.cols, CV_8UC3, Scalar(0,0,0) );
  Mat green( orig.rows, orig.cols, CV_8UC3, Scalar(0,0,0) );

  int from_to[] = { 0,0 };
  int from_to1[] = { 1,1 };
  int from_to2[] = { 2,2 };
  mixChannels( &orig, 1, &blue, 1, from_to, 1 );
  mixChannels( &orig, 1, &green, 1, from_to1, 1 );
  mixChannels( &orig, 1, &red, 1, from_to2, 1 );

  namedWindow("Image:", CV_WINDOW_AUTOSIZE);
  imshow("Image:", orig);
  namedWindow("Image-Blau:", CV_WINDOW_AUTOSIZE);
  imshow("Image-Blau:", blue);
  namedWindow("Image-Gruen:", CV_WINDOW_AUTOSIZE);
  imshow("Image-Gruen:", green);
  namedWindow("Image-Rot:", CV_WINDOW_AUTOSIZE);
  imshow("Image-Rot:", red);

  // Wait for the user to press a key in the GUI window.
  cvWaitKey(0);

  // Free the resources.
  destroyWindow("Image:");
  destroyWindow("Image-Blau:");

  return 0;
}
