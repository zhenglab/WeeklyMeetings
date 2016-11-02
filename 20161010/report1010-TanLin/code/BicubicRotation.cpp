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
	CvScalar p00,p01,p02,p03,p10,p11,p12,p13,p20,p21,p22,p23,p30,p31,p32,p33;//16个点
	CvScalar a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33;
	CvScalar F;	
	int i,j;  
        for ( i = 0; i < dst.rows; ++i){  
             
            	for ( j = 0; j < dst.cols; ++j){  			 // 输出图横轴为j，纵轴为i
               		// 旋转之后原点是（left,top），求出旋转之后的坐标点横w=j+left,纵v=i+top,
			// 旋转公式x=v*sin(alpha)+w*cos(alpha);y=v*cos(alpha)-w*sin(alpha)
                	  
                	int x = (i+top)*TransMat[0][0] + (j+left)*TransMat[1][0] ;
			int y = (i+top)*TransMat[0][1] + (j+left)*TransMat[1][1] ;  
       			// 原图横轴为y，纵轴为x；
			float ux=(int)x,uy=(int)y;
			ux=abs(ux-x);uy=abs(uy-y);	
			//取十六个点
			p00 = src.at<cv::Vec3b>((int)x-1,(int)y-1);
			p10 = src.at<cv::Vec3b>((int)x,(int)y-1);
			p20 = src.at<cv::Vec3b>((int)x+1,(int)y-1);
			p30 = src.at<cv::Vec3b>((int)x+2,(int)y-1);
			p01 = src.at<cv::Vec3b>((int)x-1,(int)y);
			p11 = src.at<cv::Vec3b>((int)x,(int)y);
			p21 = src.at<cv::Vec3b>((int)x+1,(int)y);
			p31 = src.at<cv::Vec3b>((int)x+2,(int)y);
			p02 = src.at<cv::Vec3b>((int)x-1,(int)y+1);
			p12 = src.at<cv::Vec3b>((int)x,(int)y+1);
			p22 = src.at<cv::Vec3b>((int)x+1,(int)y+1);
			p32 = src.at<cv::Vec3b>((int)x+2,(int)y+1);
			p03 = src.at<cv::Vec3b>((int)x-1,(int)y+2);
			p13 = src.at<cv::Vec3b>((int)x,(int)y+2);
			p23 = src.at<cv::Vec3b>((int)x+1,(int)y+2);
			p33 = src.at<cv::Vec3b>((int)x+2,(int)y+2);
			for(int k = 0;k < 3;k ++)
			{
				a00.val[k]=p11.val[k];

				a01.val[k]=-0.5 * p10.val[k] + 0.5 * p12.val[k];

				a02.val[k]=p10.val[k] - 2.5 * p11.val[k] + 2 * p12.val[k] - 0.5 * p13.val[k];

				a03.val[k]=-0.5 * p10.val[k] + 1.5 * p11.val[k] - 1.5 * p12.val[k] + 0.5 * p13.val[k];

				a10.val[k]=-0.5 * p01.val[k] + 0.5 * p21.val[k];

				a11.val[k]=0.25*p00.val[k]-0.25*p02.val[k]-0.25*p20.val[k]+0.25*p22.val[k];

				a12.val[k]=-0.5*p00.val[k]+1.25*p01.val[k]-p02.val[k]+0.25*p03.val[k]+0.5*p20.val[k]-1.25*p21.val[k]+p22.val[k]-0.25*p23.val[k];

				a13.val[k]=0.25*p00.val[k]-0.75*p01.val[k]+0.75*p02.val[k]-0.25*p03.val[k]-0.25*p20.val[k]+0.75*p21.val[k]-0.75*p22.val[k]+0.25*p23.val[k];

				a20.val[k]=p01.val[k]-2.5*p11.val[k]+2*p21.val[k]-0.5*p31.val[k];

				a21.val[k]=-0.5*p00.val[k]+0.5*p02.val[k]+1.25*p10.val[k]-1.25*p12.val[k]-p20.val[k]+p22.val[k]+0.25*p30.val[k]-0.25*p32.val[k];

				a22.val[k]=p00.val[k]-2.5*p01.val[k]+2*p02.val[k]-0.5*p03.val[k]-2.5*p10.val[k]+6.25*p11.val[k]-5*p12.val[k]+1.25*p13.val[k]+2*p20.val[k]-5*p21.val[k]+4*p22.val[k]-p23.val[k]-0.5*p30.val[k]+1.25*p31.val[k]-p32.val[k]+0.25*p33.val[k];

				a23.val[k]=-0.5*p00.val[k]+1.5*p01.val[k]-1.5*p02.val[k]+0.5*p03.val[k]+1.25*p10.val[k]-3.75*p11.val[k]+3.75*p12.val[k]-1.25*p13.val[k]-p20.val[k]+3*p21.val[k]-3*p22.val[k]+p23.val[k]+0.25*p30.val[k]-0.75*p31.val[k]+0.75*p32.val[k]-0.25*p33.val[k];

				a30.val[k]=-0.5*p01.val[k]+1.5*p11.val[k]-1.5*p21.val[k]+0.5*p31.val[k];
				a31.val[k]=0.25*p00.val[k]-0.25*p02.val[k]-0.75*p10.val[k]+0.75*p12.val[k]+0.75*p20.val[k]-0.75*p22.val[k]-0.25*p30.val[k]+0.25*p32.val[k];

				a32.val[k]=-0.5*p00.val[k]+1.25*p01.val[k]-p02.val[k]+0.25*p03.val[k]+1.5*p10.val[k]-3.75*p11.val[k]+3*p12.val[k]-0.75*p13.val[k]-1.5*p20.val[k]+3.75*p21.val[k]-3*p22.val[k]+0.75*p23.val[k]+0.5*p30.val[k]-1.25*p31.val[k]+p32.val[k]-0.25*p33.val[k];

				a33.val[k]=0.25*p00.val[k]-0.75*p01.val[k]+0.75*p02.val[k]-0.25*p03.val[k]-0.75*p10.val[k]+2.25*p11.val[k]-2.25*p12.val[k]+0.75*p13.val[k]+0.75*p20.val[k]-2.25*p21.val[k]+2.25*p22.val[k]-0.75*p23.val[k]-0.25*p30.val[k]+0.75*p31.val[k]-0.75*p32.val[k]+0.25*p33.val[k];


				F.val[k]=a00.val[k]+a01.val[k]*uy+a02.val[k]*uy*uy+a03.val[k]*uy*uy*uy+a10.val[k]*ux+a11.val[k]*ux*uy+a12.val[k]*ux*uy*uy+a13.val[k]*ux*uy*uy*uy+a20.val[k]*ux*ux+a21.val[k]*ux*ux*uy+a22.val[k]*ux*ux*uy*uy+a23.val[k]*ux*ux*uy*uy*uy+a30.val[k]*ux*ux*ux+a31.val[k]*ux*ux*ux*uy+a32.val[k]*ux*ux*ux*uy*uy+a33.val[k]*ux*ux*ux*uy*uy*uy;
			}
			if(F.val[0]> 255)F.val[0] = 255;
			if(F.val[1] > 255)F.val[1] = 255;
			if(F.val[2] > 255)F.val[2] = 255;
			if(F.val[0]<0)F.val[0] = 0;
			if(F.val[1]<0)F.val[1] = 0;
			if(F.val[2]<0)F.val[2] = 0;
			//系数相加为处理后的点值
			dst.at<cv::Vec3b>(i,j)[0]=F.val[0];
			dst.at<cv::Vec3b>(i,j)[1]=F.val[1];
			dst.at<cv::Vec3b>(i,j)[2]=F.val[2];	
		}
	}	
      			
	
}  
