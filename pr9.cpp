// Von Thomas
#include <stdio.h>
#include <iostream>
//#include <opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv){

  Mat img1, grey, tresh;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  // Datei öffnen
  img1 = imread("./bin/media/RegionArea01.jpg", CV_LOAD_IMAGE_COLOR);
  if (!img1.data) {
      printf("Error: Couldn't open the image file.\n");
      return 1;
  }

  // Convert to grey image
  cvtColor(img1, grey, CV_BGR2GRAY);

  threshold( grey, tresh, 180, 255, THRESH_BINARY_INV);

  // Thresh Image
  namedWindow("Thresh Image1");
  imshow("Thresh Image1",tresh);

  dilate( tresh, tresh, Mat(), Point(-1,-1), 6, BORDER_CONSTANT);
  erode ( tresh, tresh, Mat(), Point(-1,-1), 6, BORDER_CONSTANT);

  // Dilate Image
  namedWindow("Dilate Image1");
  imshow("Dilate Image1", tresh);


  findContours( tresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  Mat drawing = Mat::ones( img1.size(), CV_8U)*255;
  for( int i = 0; i < contours.size(); i++){
      drawContours(drawing, contours, i, 1, 2, 8, hierarchy, 0, Point());
      drawContours(img1, contours, i, 1, 2, 8, hierarchy, 0, Point());
  }

  //BoundingRect();

  // Contour Image
  namedWindow("Drawing");
  imshow("Drawing", drawing);

  // Orginal Image
  namedWindow("Drawing Origin");
  imshow("Drawing Origin", img1);


  /*
   * boundingRect ...
   * minEnclosingCircle
   * convexHull
   *
   * über iterator über alle punkte laufen
   *
   * Moments .. momente mom.m00 -> Flächeninhalt
   *
   *
   * 2.Teil
   * Canny
   * vector<Vec2f> lines;
   * Houghlines
   *
   * vector<Vec2f>::const_iterator it = lines.begin();
   *  while(it!= lines.end());
   * float roh = (*it)[0];
   *
   *
   * */


  /**************************************/
  /***** 2. Teil ************************/
  /**************************************/

  Mat img2;

  // Datei öffnen
  img2 = imread("./bin/media/RegionLine01.jpg", CV_LOAD_IMAGE_COLOR);
  if (!img2.data) {
      printf("Error: Couldn't open the image file.\n");
      return 1;
  }

  // Orginal Image
  namedWindow("Drawing Origin2");
  imshow("Drawing Origin2", img2);

  cvWaitKey(0);

  return 0;
}
