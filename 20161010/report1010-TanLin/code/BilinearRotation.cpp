#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include <iostream>  
#include <cmath>  
      
using namespace cv;  
using namespace std;  
#define PI 3.14159265  
    
      
      
void MyRotation(Mat& src, Mat& dst, float TransMat[3][3]);  
int main()  
{  
    	Mat image;  
      	image = imread("11.tif",1);  
      	if(!image.data)  
      	{  
        	cout << "No image data" << endl;  
          	return -1;  
      	}  
      
	imshow("image", image);  
        Mat dst;  
      	float alpha = 11.0*PI/180;  
      	float transMat[3][3] = { {cos(alpha), sin(alpha), 0}, {-sin(alpha), cos(alpha), 0}, {0, 0, 1} };
      	MyRotation(image, dst, transMat);   
      	imshow("out_image", dst);  
  	imwrite("out.jpg", dst);  
      	waitKey(0);  
      	return 0;  
}  
      
void MyRotation(Mat& src, Mat& dst, float TransMat[3][3])  
{  
         
  	float left = 0;  
        float right = 0;  
        float top = 0;  
        float down = 0;  
       //  对原图像的四个点进行求旋转之后的坐标值；公式是u=x*cos(alpha)-y*sin(alpha);v=y*cos(alpha)+x*sin(alpha)
        float x = src.cols * 1.0f;  
        float y = 0.0f;  
        float u1 = x * TransMat[0][0] + y * TransMat[1][0];  
        float v1 = x * TransMat[0][1] + y * TransMat[1][1];  
        x = src.cols * 1.0f;  
        y = src.rows * 1.0f;  
        float u2 = x * TransMat[0][0] + y * TransMat[1][0];  
        float v2 = x * TransMat[0][1] + y * TransMat[1][1];  
        x = 0.0f;  
        y = src.rows * 1.0f;  
        float u3 = x * TransMat[0][0] + y * TransMat[1][0];  
        float v3 = x * TransMat[0][1] + y * TransMat[1][1];  
      
        left = min( min( min(0.0f,u1), u2 ), u3);    //找出做左边的横坐标；
        right = max( max( max(0.0f,u1), u2 ), u3);   //找出做右边的横坐标；
        top = min( min( min(0.0f,v1), v2 ), v3);    //找出做顶部的纵坐标；
        down = max( max( max(0.0f,v1), v2 ), v3) ;   //找出做底部的纵坐标；
      
        // 定义输出图像 
        dst.create( int(abs(down-top) + 0.5),int (abs(right-left) + 0.5),src.type());  //旋转之后图像的大小
      	int i,j;  
          
        for ( i = 0; i < dst.rows; ++i){  
             
            	for ( j = 0; j < dst.cols; ++j){  			 // 输出图横轴为j，纵轴为i
               		// 旋转之后原点是（left,top），求出旋转之后的坐标点横w=j+left,纵v=i+top,
			// 旋转公式x=v*sin(alpha)+w*cos(alpha);y=v*cos(alpha)-w*sin(alpha)
                	int x = (i+top)*TransMat[0][1] + (j+left)*TransMat[1][1] ;  
                	int y = (i+top)*TransMat[0][0] + (j+left)*TransMat[1][0] ;  
       			// 原图横轴为x，纵轴为y；
      			int iv = (int)x;  
            		int iu = (int)y;  
  
            		CvScalar p1, p2, p3, p4;  
            		p1=src.at<cv::Vec3b>( iu, iv);  
           		p2=src.at<cv::Vec3b>( iu, (iv+1));  
            		p3=src.at<cv::Vec3b>( (iu+1), iv);  
            		p4=src.at<cv::Vec3b>((iu+1), (iv+1));  
  
           		dst.at<cv::Vec3b>(i,j)[0] = (p1.val[0]*(1-abs(y-iu)) + p3.val[0]*abs(y-iu))*(1-abs(x-iv)) + (p2.val[0]*(1-abs(y-iu))+p4.val[0]*abs(y-iu))*abs(x-iv);  
           		dst.at<cv::Vec3b>(i,j)[1] = (p1.val[1]*(1-abs(y-iu)) + p3.val[1]*abs(y-iu))*(1-abs(x-iv)) + (p2.val[1]*(1-abs(y-iu))+p4.val[1]*abs(y-iu))*abs(x-iv);  
           		dst.at<cv::Vec3b>(i,j)[2] = (p1.val[2]*(1-abs(y-iu)) + p3.val[2]*abs(y-iu))*(1-abs(x-iv)) + (p2.val[2]*(1-abs(y-iu))+p4.val[2]*abs(y-iu))*abs(x-iv);  
       
          
      
                
                  
        	}
	}  
}  
