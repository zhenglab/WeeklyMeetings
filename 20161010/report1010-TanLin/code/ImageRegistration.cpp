#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <cmath>  
      
using namespace cv;  
using namespace std;  

void MyRotation(Mat& src, Mat& dst,float s);  
int main()  
{  
    	Mat src = imread("1.tif",1);  
      	if(!src.data)  
      	{  
        	cout << "No image data" << endl;  
          	return -1;  
      	}  
      
	imshow("image", src);  
        Mat dst;
        float s=0.1;
	int x,y;
	int r = src.rows;
	int c = src.cols;
	dst.create(1.1*r,1.1*c  ,src.type());
	for(int i = 0;i < src.rows;i ++)
	{	
		for(int j = 0;j < src.cols;j ++)
		{	
			x = i + s * j;
			y = s * i + j;
			dst.at<Vec3b>(x,y)[0] = src.at<Vec3b>(i,j)[0];
			dst.at<Vec3b>(x,y)[1] = src.at<Vec3b>(i,j)[1];
			dst.at<Vec3b>(x,y)[2] = src.at<Vec3b>(i,j)[2];
		
 		}
	}
      	imshow("distorted_image", dst);  
  	imwrite("distorted_image.jpg", dst); 
      	waitKey(0);  
      	return 0;  
	
}
