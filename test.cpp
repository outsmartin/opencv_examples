#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main ()
{
  Mat image;
  image = imread("./bin/media/test.jpg");
  // Display the image.
  namedWindow("Image:");
  imshow("Image:", image);
  // Wait for the user to press a key in the GUI window.
  waitKey(0);
  // Free the resources.
  destroyWindow("Image:");
  return 0;
}
