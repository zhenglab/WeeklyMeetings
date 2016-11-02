#include <iostream> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace cv;
using namespace std;

    int main(int argc, char* argv[])  
    {
	//放大倍数  
	double x=2;

        //读图语句报错
	if ( argc != 2 )
	{
		cout<<"Wrong arguments."<<endl;
		cout<<"Usage:"<<endl;
		cout<<"\t "<<argv[0]<<" Image"<<endl;
		exit(7);
	}

	string image = argv[1];
        Mat src = imread(image);  
       
	//读图格式报错
	if( !src.data )
	{
		cout<<"Can't process this kind of image"<<endl;
		exit(8);
	}

        //显示  
        imshow("src",src);  
      
        //处理长宽  
	int row=src.rows;
	int col=src.cols;
	float nrow=x*(float)row;
	float ncol=x*(float)col;
	
	//创建矩阵
        Mat dst = Mat::zeros(nrow,ncol,CV_8UC3);  
      	
	float X=0,Y=0;
	CvScalar a,b,c,d;

	//双线性内插
	for ( int i = 0; i < nrow-1; i++)
	{
		for(int j = 0; j < ncol-1; j++)
		{
			X= i / (double)x ;
			Y= j / (double)x ;
			float ux=(int)X,uy=(int)Y;
			ux=abs(ux-X);uy=abs(uy-Y);
			
			if( X < row-1 && X >= 0 && Y >= 0 && Y < col-1 )
			{
		//取四个点
			a = src.at<cv::Vec3b>((int)X,(int)Y);
			b = src.at<cv::Vec3b>((int)X,(int)Y+1);
			c = src.at<cv::Vec3b>((int)X+1,(int)Y);
			d = src.at<cv::Vec3b>((int)X+1,(int)Y+1);
			}
		//系数相加为处理后的点值
				dst.at<cv::Vec3b>(i,j)[0]=(a.val[0]*(1-ux)+c.val[0]*ux)*(1-uy)+(b.val[0]*(1-ux)+d.val[0]*ux)*uy;
				dst.at<cv::Vec3b>(i,j)[1]=(a.val[1]*(1-ux)+c.val[1]*ux)*(1-uy)+(b.val[1]*(1-ux)+d.val[1]*ux)*uy;
				dst.at<cv::Vec3b>(i,j)[2]=(a.val[2]*(1-ux)+c.val[2]*ux)*(1-uy)+(b.val[2]*(1-ux)+d.val[2]*ux)*uy;
			
		}
	}        


      
        imshow("dst",dst);  
      	imwrite("Bilinear-pots.jpg",dst);

        waitKey(0);  
        return 0;  
    }  



