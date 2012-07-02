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
void doFourier(){
  Mat padded;
  Mat I = grey.clone();
  int m = getOptimalDFTSize( I.rows );
  int n = getOptimalDFTSize( I.cols ); // on the border add zero values
  copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

  Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
  Mat complexI;
  merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

  dft(complexI, complexI);            // this way the result may fit in the source matrix

  // compute the magnitude and switch to logarithmic scale
  // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
  split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
  magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
  Mat magI = planes[0];

  magI += Scalar::all(1);                    // switch to logarithmic scale
  log(magI, magI);

  // crop the spectrum, if it has an odd number of rows or columns
  magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

  // rearrange the quadrants of Fourier image  so that the origin is at the image center
  int cx = magI.cols/2;
  int cy = magI.rows/2;

  Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
  Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
  Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
  Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

  Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);

  q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
  q2.copyTo(q1);
  tmp.copyTo(q2);

  normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
  // viewable image form (float between values 0 and 1).

  imshow("Input Image"       , I   );    // Show the result
  imshow("spectrum magnitude", magI);

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
  doFourier();

  // Wait for the user to press a key in the GUI window.
  cvWaitKey(0);

  return 0;
}
