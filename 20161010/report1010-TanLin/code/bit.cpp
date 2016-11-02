#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{

    Mat srcimage = imread("11.tif");
   if(!srcimage.data)

   {

      cout << "image read is error!" << endl;

      return 0;

    }

    cout << "image Info:Height:" << srcimage.size().height << " Width:" << srcimage.size().width << endl;

    imshow("Original ", srcimage);

    imwrite("original.jpg", srcimage);
    
    Mat dstimage= imread("Bit_Level_1.jpg");
    Mat dstimage2;

    dstimage.create(srcimage.rows,srcimage.cols,srcimage.type());

    dstimage2.create(srcimage.rows,srcimage.cols,srcimage.type());

    int r = srcimage.rows;

    int c = srcimage.cols * srcimage.channels();

    int h = srcimage.cols;

    if(srcimage.isContinuous())

    {

      c = c * r;

      r = 1;

    }

    int i,j;

    uchar* data;

    uchar* data_tmp;

      for(i = 0; i < r; i ++)

      {

        data = srcimage.ptr<uchar>(i);

        data_tmp = dstimage.ptr<uchar>(i);
 
        for(j = 0; j < c; j ++)

        {    //最低阶比特置0；

          if(data[j] >= 0 && data[j] < 2)

              data_tmp[j] = 0;

          else

             data_tmp[j] =data[j];

      }

     }
     imshow("Bit Level 1", dstimage);

     imwrite("Bit_Level_1.jpg", dstimage);
   
     waitKey(0);

     return 0;
}



