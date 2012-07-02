#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
  using namespace cv;
  using namespace std;
int main ()
{
  // Open the file.
  Mat orig,image1;
  orig = imread("pr3.jpg");

  namedWindow("Image:", CV_WINDOW_AUTOSIZE);
  namedWindow("ROI:", CV_WINDOW_AUTOSIZE);
  image1 = orig(Rect(50,50,450,350));
  int lightsumr=0, lightsumg=0, lightsumb=0, count=0;
  for(int j = 0; j <= image1.rows; j++) {
    for(int i = 0; i <= image1.cols; i++) {
      lightsumb += image1.at<Vec3b>(Point(i,j))[0];
      image1.at<Vec3b>(Point(i,j))[0] += (255-image1.at<Vec3b>(Point(i,j))[0])/2;
      lightsumg += image1.at<Vec3b>(Point(i,j))[1];
      image1.at<Vec3b>(Point(i,j))[1] += (255-image1.at<Vec3b>(Point(i,j))[1])/2;
      lightsumr += image1.at<Vec3b>(Point(i,j))[2];
      image1.at<Vec3b>(Point(i,j))[2] += (255-image1.at<Vec3b>(Point(i,j))[2])/2;
      count++;
    }
  }
  cout << "R:" << lightsumr/count << " G:" << lightsumg/count << " B:" << lightsumb/count << " sum:" << count << endl;

  rectangle(orig,Point(50,50),Point(500,400),Scalar(255,255,255),3,8);
  imshow("Image:", orig);

  imshow("ROI:", image1);


  // Wait for the user to press a key in the GUI window.
  cvWaitKey(0);

  return 0;
}
