#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
using namespace cv;
using namespace std;
//Globale Variablen
Mat img,img0;
//Variablen fuer Slider
const int slider_max = 100;
int slider_pos = 0;

void help()
{
  cout << "\nPraktikum 2b \n" << "Using OpenCV version %s\n" << CV_VERSION << "\n";
  cout << "Usage:\n" "./pr2b \n" << endl;
  cout << "Hot keys: \n"
          "\ti - show/refresh the changed image\n"
          "\tq - quit the program\n" << endl;
}
void brightnessSliderChanged(int, void*){
  // slider debug:
  // cout << "Aktuelle Helligkeit: "<< slider_pos  << endl;
  img = Mat::zeros( img0.size(), img0.type());
  double alpha=1.0;
  int beta = slider_pos;
  for( int y = 0; y < img0.rows; y++ )
  { for( int x = 0; x < img0.cols; x++ )
    { for( int c = 0; c < 3; c++ )
      {
        img.at<Vec3b>(y,x)[c] =
          saturate_cast<uchar>( alpha*( img0.at<Vec3b>(y,x)[c] ) + beta );
      }
    }
  }
}
void onMouse( int event, int x, int y, int flags, void* ){
  Mat img_backup;
  stringstream text("");
  text << "Punkt: " << x << "," << y;
  if (x < img0.rows && y < img0.cols)
    text << "Farbwert: " << (int)img0.at<Vec3b>(x,y)[0] << ","
      << (int)img0.at<Vec3b>(x,y)[1] << ","
      << (int)img0.at<Vec3b>(x,y)[2];
  img_backup = img0.clone();
  putText(img0,text.str(), cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
  imshow("Image:", img0);
  img0 = img_backup.clone();
}
int main( int argc, char** argv )
{
  // Open the file.
  char* filename = argc >= 2 ? argv[1] : (char*)"./bin/media/pr2.jpg";
  img0 = imread(filename, -1);
  // Is image present?
  if(img0.empty())
  {
    cout << "Couldn't open the image " << filename << ". Usage: pr2 <image_name>\n" << endl;
    return 0;
  }
  help();

  namedWindow("Image:", CV_WINDOW_AUTOSIZE);
  imshow("Image:", img0);
  //get the mouse
  setMouseCallback("Image:", onMouse, 0 );
  // add the slider
  createTrackbar("brightness","Image:",&slider_pos,slider_max,brightnessSliderChanged);
  // key loop
  for(;;)
  {
    char c = (char)waitKey();

    if( c == 'q' )
      break;

    if( c == 'r' )
    {
      img0.copyTo(img);
      imshow("image", img);
    }

    if( c == 'i' || c == ' ' )
    {
      imshow("Helligkeit:", img);
    }
  }
  return 0;
}
