#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{

    Mat srcimage = imread("11.tif");
    
    imshow("Original ", srcimage);

    imwrite("original.jpg", srcimage);
    
    Mat dstimage= imread("Bit_Level_1.jpg");

    Mat dstimage2;

    dstimage2.create(srcimage.rows,srcimage.cols,srcimage.type());

    int r = srcimage.rows;

    int h = srcimage.cols;

      for(int k = 0;k < r;k ++)
      {
       
        for(int w =0;w < h;w ++)
         {
             
            dstimage2.at<Vec3b>(k,w)[0] = srcimage.at<Vec3b>(k,w)[0] - dstimage.at<Vec3b>(k,w)[0];
         
            dstimage2.at<Vec3b>(k,w)[1] = srcimage.at<Vec3b>(k,w)[1] - dstimage.at<Vec3b>(k,w)[1];

            dstimage2.at<Vec3b>(k,w)[2] = srcimage.at<Vec3b>(k,w)[2] - dstimage.at<Vec3b>(k,w)[2];
         
          }
      }
       
      imshow("sub", dstimage2);

      imwrite("sub.jpg", dstimage2);

      waitKey(0);

      return 0;
}



