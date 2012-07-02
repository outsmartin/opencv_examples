#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat orig,grey;
int _brightness = 100;
int _contrast = 100;

void calcHistogram(int, void*){
  int histSize = 64;
  Mat dst, hist;
  int brightness = _brightness - 100;
  int contrast = _contrast - 100;

  double a, b;
  if( contrast > 0 )
  {
    double delta = 127.*contrast/100;
    a = 255./(255. - delta*2);
    b = a*(brightness - delta);
  }
  else
  {
    double delta = -128.*contrast/100;
    a = (256.-delta*2)/255.;
    b = a*brightness + delta;
  }
  grey.convertTo(dst, CV_8U, a, b);
  calcHist(&dst, 1, 0, Mat(), hist, 1, &histSize, 0);
  Mat histImage = Mat::ones(200, 320, CV_8U)*255;

  normalize(hist, hist, 0, histImage.rows, CV_MINMAX, CV_32F);

  histImage = Scalar::all(255);
  int binW = cvRound((double)histImage.cols/histSize);

  for( int i = 0; i < histSize; i++ )
    rectangle( histImage, Point(i*binW, histImage.rows),
        Point((i+1)*binW, histImage.rows - cvRound(hist.at<float>(i))),
        Scalar::all(0), -1, 8, 0 );
  imshow("histogram", histImage);
}
int main ()
{
  // Open the file.
  int PYRAMIDE_STUFEN = 3;
  vector<Mat>pyramid;
  orig = imread("pr5.jpg");

  cvtColor(orig,grey,CV_RGB2GRAY);

  namedWindow("Image:", CV_WINDOW_AUTOSIZE);
  namedWindow("Grey:", CV_WINDOW_AUTOSIZE);
  imshow("Image:", orig);
  imshow("Grey:", grey);
  buildPyramid(orig,pyramid,PYRAMIDE_STUFEN);
  imshow("Pyramide1:",pyramid[1]);
  calcHistogram(0,0);

  // Wait for the user to press a key in the GUI window.
  cvWaitKey(0);

  return 0;
}
