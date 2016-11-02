#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
float Abs(float f);  
void zoom(Mat& src, Mat& dst);  
  
int main()
{  
  
   Mat src = imread("72dpi.jpg");  
   Mat dst; 
   dst.create(cvSize(174,230), src.type());  
   zoom(src, dst);  
  
   imshow("src", src);  
   imshow("dst", dst); 
   imwrite("150dpi.jpg",dst); 
   waitKey(0);  
  
   return 0; 
}  

//返回绝对值 

float Abs(float f)  
{  
    return f>=0 ? f : -f;  
}  

void zoom(Mat& src, Mat& dst)
{  
    int sr = src.rows;  
    int sc = src.cols;  
    int c = dst.cols;  
    int r = dst.rows;  
  
    //源图像与目标图像的宽高比例
    const float tx = (sr-1.0f)/(r-1.0f);  
    const float ty = (sc-1.0f)/(c-1.0f);  
    
  
    for (int j=0; j<c-1; j++)  
     {  
         for (int i=0; i<r-1; i++)  
         {  
            float x = i*tx;  
            float y = j*ty;  
  
            int iu = (int)x;  
            int iv = (int)y;  
  
            CvScalar p1, p2, p3, p4;  
            p1=src.at<cv::Vec3b>( iu, iv);  
            p2=src.at<cv::Vec3b>( iu, (iv+1));  
            p3=src.at<cv::Vec3b>( (iu+1), iv);  
            p4=src.at<cv::Vec3b>((iu+1), (iv+1));  
  
           dst.at<cv::Vec3b>(i,j)[0] = (p1.val[0]*(1-abs(x-iu)) + p3.val[0]*abs(x-iu))*(1-abs(y-iv)) + (p2.val[0]*(1-abs(x-iu))+p4.val[0]*abs(x-iu))*abs(y-iv);  
           dst.at<cv::Vec3b>(i,j)[1] = (p1.val[1]*(1-abs(x-iu)) + p3.val[1]*abs(x-iu))*(1-abs(y-iv)) + (p2.val[1]*(1-abs(x-iu))+p4.val[1]*abs(x-iu))*abs(y-iv);  
           dst.at<cv::Vec3b>(i,j)[2] = (p1.val[2]*(1-abs(x-iu)) + p3.val[2]*abs(x-iu))*(1-abs(y-iv)) + (p2.val[2]*(1-abs(x-iu))+p4.val[2]*abs(x-iu))*abs(y-iv);  
       
         }  
         //这里添加上最后一行  
        dst.at<cv::Vec3b>(r-1,j)[0] = dst.at<cv::Vec3b>(r-2,j)[0];
        dst.at<cv::Vec3b>(r-1,j)[1] = dst.at<cv::Vec3b>(r-2,j)[1];
        dst.at<cv::Vec3b>(r-1,j)[2] = dst.at<cv::Vec3b>(r-2,j)[2];

        
    }  
    //这里添加上最后一列  
    for(int i=0; i<r; i++)  
    {  
        dst.at<cv::Vec3b>(i,c-1)[0] = dst.at<cv::Vec3b>(i,c-2)[0];
        dst.at<cv::Vec3b>(i,c-1)[1] = dst.at<cv::Vec3b>(i,c-2)[1];
        dst.at<cv::Vec3b>(i,c-1)[2] = dst.at<cv::Vec3b>(i,c-2)[2];  
    }  
}  
