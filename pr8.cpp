/*
 * von Thomas
 * Praktikum 8: Merkmalsextraktion
 *
 */

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
  double delta;
  int ddepth;

  // Datei öffnen
  image1 = imread("./bin/media/pr8.jpg", CV_LOAD_IMAGE_COLOR);

  // Convert to grey image
  cvtColor(image1, src, CV_BGR2GRAY);

  // Init Arguments for Filter
  anchor = Point( -1, -1);
  delta = 0;
  ddepth = -1;

  // Normal Image
  namedWindow("Normal Image");
  imshow("Normal Image",image1);

  // Grey Image
  namedWindow("Grey Image");
  imshow("Grey Image",src);

  //!!threshold(src,dst, 200, 255, TRESH_BINARY);


  /************************/
  /*** Filter 1.Ordnung ***/
  /************************/
  double m1[3][1] ={1,0,-1};
  Mat kernel1 = Mat(3,1, CV_64F, m1);

  double m2[1][3] ={1,0,-1};
  Mat kernel2 = Mat(1,3, CV_64F, m2);

  // Filter anwenden
  filter2D( src, dst1, ddepth, kernel1, anchor, delta, BORDER_DEFAULT);
  filter2D( src, dst2, ddepth, kernel2, anchor, delta, BORDER_DEFAULT);

  max(dst1, dst2, dst);

  // Anzeigen
  namedWindow("Filter 1.Ordnung - horizontal");
  imshow("Filter 1.Ordnung - horizontal", dst1);

  // Anzeigen
  namedWindow("Filter 1.Ordnung - vertikal");
  imshow("Filter 1.Ordnung - vertikal", dst2);

  // Anzeigen
  namedWindow("Filter 1.Ordnung");
  imshow("Filter 1.Ordnung", dst+100);


  /*************************************/
  /*** Laplace-Filter 2D (2.Ordnung) ***/
  /*************************************/

  double m3[3][3] ={{0,1,0}, {1,-4,1}, {0,1,0}};
  Mat kernel3 = Mat(3,3, CV_64F, m3);

  // Filter anwenden
  filter2D( src, dst, ddepth, kernel3, anchor, delta, BORDER_DEFAULT);

  // Anzeigen
  namedWindow("Filter 2.Ordnung");
  imshow("Filter 2.Ordnung",dst);


  /********************/
  /*** Sobel-Filter ***/
  /********************/
  double m4[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};
  Mat kernel4 = Mat(3,1, CV_64F, m4);

  double m5[3][3] = {{1,0,-1}, {2,0,-2}, {1,0,-1}};
  Mat kernel5 = Mat(1,3, CV_64F, m5);

  // Filter anwenden
  filter2D( src, dst4, ddepth, kernel4, anchor, delta, BORDER_DEFAULT);
  filter2D( src, dst5, ddepth, kernel5, anchor, delta, BORDER_DEFAULT);

  //max(dst4, dst5, dst3);

  // Anzeigen
  namedWindow("Sobel Filter - horizontal");
  imshow("Sobel Filter - horizontal", dst1);

  // Anzeigen
  namedWindow("Sobel Filter - vertikal");
  imshow("Sobel Filter - vertikal", dst2);

  // Anzeigen
  //namedWindow("Sobel Filter");
  //imshow("Sobel Filter", dst3);



  /********************/
  /* Texturanalyse    */
  /********************/

  // Datei öffnen
  image2 = imread("./bin/media/Text01.jpg", CV_LOAD_IMAGE_COLOR);
  if (!image2.data) {
      printf("Error: Couldn't open the image file.\n");
      return 1;
  }

  // Convert to grey image
  cvtColor(image2, src, CV_BGR2GRAY);

  // Normal Image
  namedWindow("Normal Image2");
  imshow("Normal Image2",image2);

  // Grey Image
  namedWindow("Grey Image2");
  imshow("Grey Image2",src);


 //meanstddev(..);


 //calcHist
  // compareHist

  cvWaitKey(0);

  return 0;
}
