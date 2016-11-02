#include <iostream>
#include <cmath>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{

    Mat srcimage = imread("72dpi.jpg");
    if(!srcimage.data)

    {

        cout << "image read is error!" << endl;

        return 0;

    }
    cout << "image Info:Height:" << srcimage.size().height << " Width:" << srcimage.size().width << endl;
    imshow("origin",srcimage);
    int n = 2;
    int W = srcimage.rows;
    int H = srcimage.cols;
    int w = W*n;
    int h=H*n;
    Mat dstimage;                                                         //定义一个输出图像；
    dstimage.create(w,h,srcimage.type());                                 //定义输出图像的大小、类型； 
    for(int i=0;i<w;i++)
    { 
    	for(int j=0;j<h;j++)
        {	
     	   int x=int(float(i)/float(n)+0.5);
           int y=int(float(j)/float(n)+0.5);
           dstimage.at<Vec3b>(i,j)[0] = srcimage.at<Vec3b>(x,y)[0];  
           dstimage.at<Vec3b>(i,j)[1] = srcimage.at<Vec3b>(x,y)[1];
           dstimage.at<Vec3b>(i,j)[2] = srcimage.at<Vec3b>(x,y)[2];
        }
    }
   //这里添加上最后一行  
    for(int j=0; j<h; j++)  
    {  
        dstimage.at<cv::Vec3b>(w-1,j)[0] = dstimage.at<cv::Vec3b>(w-2,j)[0];
        dstimage.at<cv::Vec3b>(w-1,j)[1] = dstimage.at<cv::Vec3b>(w-2,j)[1];
        dstimage.at<cv::Vec3b>(w-1,j)[2] = dstimage.at<cv::Vec3b>(w-2,j)[2];

    } 
    imshow("fangdatu",dstimage);
    imwrite("fada150.jpg", dstimage);
    waitKey(0);
    return 0;
}
