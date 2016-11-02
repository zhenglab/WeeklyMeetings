#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat srcimage1 = imread("11.tif");
    	imshow("Original", srcimage1);
	Mat srcimage2 = imread("22.tif");
        imshow("yinying", srcimage2);
      	int r1 = srcimage1.rows;
      	int c1 = srcimage1.cols;
      	int r2 = srcimage2.rows;
      	int c2 = srcimage2.cols;
        Mat dstimage;
        dstimage.create(r1,c1,srcimage1.type());
        for(int i = 0;i < r2;i++){
        	for(int j = 0;j < c2;j++){
               		if (srcimage2.at<Vec3b>(i,j)[0] > 0) srcimage2.at<Vec3b>(i,j)[0] = 1;
			if (srcimage2.at<Vec3b>(i,j)[1] > 0) srcimage2.at<Vec3b>(i,j)[1] = 1;  
                	if (srcimage2.at<Vec3b>(i,j)[2] > 0) srcimage2.at<Vec3b>(i,j)[2] = 1;         
             	}       
       	}
        for(int i = 0;i < r1;i++){
            	for(int j = 0;j < c1;j++){
              	dstimage.at<Vec3b>(i,j)[0] = srcimage1.at<Vec3b>(i,j)[0]*srcimage2.at<Vec3b>(i,j)[0];
              	dstimage.at<Vec3b>(i,j)[1] = srcimage1.at<Vec3b>(i,j)[1]*srcimage2.at<Vec3b>(i,j)[1];            
              	dstimage.at<Vec3b>(i,j)[2] = srcimage1.at<Vec3b>(i,j)[2]*srcimage2.at<Vec3b>(i,j)[2]; 
            	}
      	} 
      	imshow("xiaoguotu", dstimage);
	imwrite("xiaoguotu.jpg", dstimage);
	waitKey(0);
	return 0;
}
