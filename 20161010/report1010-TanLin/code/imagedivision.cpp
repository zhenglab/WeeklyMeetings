#include <iostream> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
	Mat srcimage1 = imread("1.tif");
    	imshow("Original", srcimage1);
	imwrite("Original.jpg", srcimage1);
	Mat srcimage2 = imread("2.tif");
        imshow("yinying", srcimage2);
	imwrite("Original2.jpg", srcimage2);
      	int r1 = srcimage1.rows;
      	int c1 = srcimage1.cols;
      	int r2 = srcimage2.rows;
      	int c2 = srcimage2.cols;
        Mat dstimage;
        dstimage.create(r1,c1,srcimage1.type());
	CvScalar A,F;
	for(int i = 0;i < r1;i ++)
	{	
		for(int j = 0;j < c1;j ++)
		{
			A.val[0] = srcimage2.at<Vec3b>(i,j)[0] / 255.0;
			A.val[1] = srcimage2.at<Vec3b>(i,j)[1] / 255.0;
			A.val[2] = srcimage2.at<Vec3b>(i,j)[2] / 255.0;
			F.val[0] = srcimage1.at<Vec3b>(i,j)[0] / A.val[0];
			F.val[1] = srcimage1.at<Vec3b>(i,j)[1] / A.val[1];
			F.val[2] = srcimage1.at<Vec3b>(i,j)[2] / A.val[2];
			if(F.val[0] > 255) F.val[0] = 255;
			if(F.val[1] > 255) F.val[1] = 255;
			if(F.val[2] > 255) F.val[2] = 255;
			dstimage.at<Vec3b>(i,j)[0] = (int)F.val[0];
			dstimage.at<Vec3b>(i,j)[1] = (int)F.val[1];
			dstimage.at<Vec3b>(i,j)[2] = (int)F.val[2];
		}	
	}
	imshow("result",dstimage);
	imwrite("result.jpg",dstimage);
	waitKey(0);    
	return 0;    
}  

