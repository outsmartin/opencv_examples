#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat orig,image1;
int main ()
{
  // Open the file.
  orig = imread("./bin/media/pr3.jpg");
  image1 = orig.clone();
  namedWindow("Image:", CV_WINDOW_AUTOSIZE);
  namedWindow("ROI:", CV_WINDOW_AUTOSIZE);
  for(int j = 0; j <= image1.rows; j++) {
    for(int i = 0; i <= image1.cols; i++) {
      image1.at<Vec3b>(Point(i,j))[0] += (255-image1.at<Vec3b>(Point(i,j))[0])/2;
      image1.at<Vec3b>(Point(i,j))[1] += (255-image1.at<Vec3b>(Point(i,j))[1])/2;
      image1.at<Vec3b>(Point(i,j))[2] += (255-image1.at<Vec3b>(Point(i,j))[2])/2;
    }
  }

  imshow("Image:", orig);

  imshow("ROI:", image1);


  // Wait for the user to press a key in the GUI window.
  cvWaitKey(0);

  return 0;
}
