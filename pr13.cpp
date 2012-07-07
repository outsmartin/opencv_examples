
#include <stdio.h>
#include <iostream>
//#include <opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace std;
using namespace cv;


int main(int argc, char** argv){

  Mat image1, image2, src, dst, dst1, dst2, dst3, dst4, dst5;
  Point anchor;
  int w,W,h,H;

  // Datei öffnen
  image1 = imread("./bin/media/Blatt11.bmp", CV_LOAD_IMAGE_COLOR);

  // Convert to grey image
  cvtColor(image1, src, CV_BGR2GRAY);

  // Init Arguments for Filter

  // Normal Image
  namedWindow("Normal Image");
  imshow("Normal Image",image1);

  // Grey Image
  namedWindow("Grey Image");
  imshow("Grey Image",src);
}
