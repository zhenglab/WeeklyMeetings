#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{

    Mat srcimage1 = imread("4noise.jpg");
    Mat srcimage2 = imread("8noise.jpg");
    Mat srcimage3 = imread("16noise.jpg");
    Mat srcimage4 = imread("64noise.jpg");
    Mat srcimage5 = imread("128noise.jpg");
    imshow("origin1",srcimage1);
    imshow("origin2",srcimage2);
    imshow("origin3",srcimage3);
    imshow("origin4",srcimage4);
    imshow("origin5",srcimage5);
    Mat dstimage;
    dstimage.create(srcimage1.rows,srcimage1.cols,srcimage1.type());
    int r=srcimage1.rows;
    int c=srcimage1.cols;
    CvScalar sum; 
    for(int i=0;i<r;i++)
    {
       for(int j=0;j<c;j++)
       {
          sum.val[0]=srcimage1.at<Vec3b>(i,j)[0]+srcimage2.at<Vec3b>(i,j)[0]+srcimage3.at<Vec3b>(i,j)[0]+srcimage4.at<Vec3b>(i,j)[0]+srcimage5.at<Vec3b>(i,j)[0] ;
          sum.val[1]=srcimage1.at<Vec3b>(i,j)[1]+srcimage2.at<Vec3b>(i,j)[1]+srcimage3.at<Vec3b>(i,j)[1]+srcimage4.at<Vec3b>(i,j)[1]+srcimage5.at<Vec3b>(i,j)[1] ;
          sum.val[2]=srcimage1.at<Vec3b>(i,j)[2]+srcimage2.at<Vec3b>(i,j)[2]+srcimage3.at<Vec3b>(i,j)[2]+srcimage4.at<Vec3b>(i,j)[2]+srcimage5.at<Vec3b>(i,j)[2] ;  
          dstimage.at<Vec3b>(i,j)[0]=sum.val[0]/5;
          dstimage.at<Vec3b>(i,j)[1]=sum.val[1]/5;
          dstimage.at<Vec3b>(i,j)[2]=sum.val[2]/5;
    
  
       }
    }

    imshow("ff",dstimage);
    imwrite("5avg.jpg",dstimage);
    waitKey(0);
    return 0;

}
