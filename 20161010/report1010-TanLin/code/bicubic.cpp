#include <iostream> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace cv;
using namespace std;

void zoom(Mat& src, Mat& dst,double x);  
int main()
{  
  
   Mat src = imread("72dpi.jpg"); 
   //处理长宽  
   int row=src.rows;//原图长宽
   int col=src.cols;
   double x=2;
   float nrow=x*(float)row;//新图长宽
   float ncol=x*(float)col; 
   Mat dst; 
   dst.create(nrow,ncol,src.type());  
   zoom(src, dst,2);  
  
   imshow("src", src);  
   imshow("dst", dst); 
   imwrite("150dpi.jpg",dst); 
   waitKey(0);  
  
   return 0; 
}  

void zoom(Mat& src, Mat& dst,double x)
{
	int row=src.rows;
   	int col=src.cols;
   	float nrow=dst.rows;
   	float ncol=dst.cols;
      	
	float X=0,Y=0;

	CvScalar p00,p01,p02,p03,p10,p11,p12,p13,p20,p21,p22,p23,p30,p31,p32,p33;//16个点
	CvScalar a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,a23,a30,a31,a32,a33;
	CvScalar F;

	//双三次内插
	for ( int i = 1;i < nrow-1;i ++)//i,j:新图的每个点
	{
		for(int j = 1;j < ncol-1;j ++)
		{
			X= i / (double)x ;//原图上的位置(X,Y)
			Y= j / (double)x ;
			float ux=(int)X,uy=(int)Y;
			ux=abs(ux-X);uy=abs(uy-Y);		

			if( X < row - 1 && X > 0 && Y > 0 && Y < col - 1 )
			{
			//取十六个点
				p00 = src.at<cv::Vec3b>((int)X-1,(int)Y-1);
				p10 = src.at<cv::Vec3b>((int)X,(int)Y-1);
				p20 = src.at<cv::Vec3b>((int)X+1,(int)Y-1);
				p30 = src.at<cv::Vec3b>((int)X+2,(int)Y-1);
				p01 = src.at<cv::Vec3b>((int)X-1,(int)Y);
				p11 = src.at<cv::Vec3b>((int)X,(int)Y);
				p21 = src.at<cv::Vec3b>((int)X+1,(int)Y);
				p31 = src.at<cv::Vec3b>((int)X+2,(int)Y);
				p02 = src.at<cv::Vec3b>((int)X-1,(int)Y+1);
				p12 = src.at<cv::Vec3b>((int)X,(int)Y+1);
				p22 = src.at<cv::Vec3b>((int)X+1,(int)Y+1);
				p32 = src.at<cv::Vec3b>((int)X+2,(int)Y+1);
				p03 = src.at<cv::Vec3b>((int)X-1,(int)Y+2);
				p13 = src.at<cv::Vec3b>((int)X,(int)Y+2);
				p23 = src.at<cv::Vec3b>((int)X+1,(int)Y+2);
				p33 = src.at<cv::Vec3b>((int)X+2,(int)Y+2);
			}

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
			if(F.val[0]> 255)
				{F.val[0] = 255;}

			if(F.val[1] > 255)
				{F.val[1] = 255;}

			if(F.val[2] > 255)
				{F.val[2] = 255;}
			if(F.val[0]<0)
				{F.val[0] = 0;}

			if(F.val[1]<0)
				{F.val[1] = 0;}

			if(F.val[2]<0)
				{F.val[2] = 0;}

			//系数相加为处理后的点值
			dst.at<cv::Vec3b>(i,j)[0]=F.val[0];
			dst.at<cv::Vec3b>(i,j)[1]=F.val[1];
			dst.at<cv::Vec3b>(i,j)[2]=F.val[2];	
		}
           	 
        	//这里添加上最后一列
        	dst.at<cv::Vec3b>(i,ncol-1)[0] = dst.at<cv::Vec3b>(i,ncol-2)[0];
        	dst.at<cv::Vec3b>(i,ncol-1)[1] = dst.at<cv::Vec3b>(i,ncol-2)[1];
        	dst.at<cv::Vec3b>(i,ncol-1)[2] = dst.at<cv::Vec3b>(i,ncol-2)[2]; 
		//这里添加上第一列
		dst.at<cv::Vec3b>(i,0)[0] = dst.at<cv::Vec3b>(i,1)[0];
        	dst.at<cv::Vec3b>(i,0)[1] = dst.at<cv::Vec3b>(i,1)[1];
        	dst.at<cv::Vec3b>(i,0)[2] = dst.at<cv::Vec3b>(i,1)[2];  
	} 		
	for(int j=0; j<ncol; j++){ //这里添加上最后一行   
        	dst.at<cv::Vec3b>(nrow-1,j)[0] = dst.at<cv::Vec3b>(nrow-2,j)[0];
        	dst.at<cv::Vec3b>(nrow-1,j)[1] = dst.at<cv::Vec3b>(nrow-2,j)[1];
        	dst.at<cv::Vec3b>(nrow-1,j)[2] = dst.at<cv::Vec3b>(nrow-2,j)[2];
		//这里添加上第一行 
		dst.at<cv::Vec3b>(0,j)[0] = dst.at<cv::Vec3b>(1,j)[0];
        	dst.at<cv::Vec3b>(0,j)[1] = dst.at<cv::Vec3b>(1,j)[1];
        	dst.at<cv::Vec3b>(0,j)[2] = dst.at<cv::Vec3b>(1,j)[2];
			
		
    }    
}  

