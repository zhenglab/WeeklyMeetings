#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
void Fuzzysets(Mat& src1,Mat& dst1,int m,int n);
int main()
{
	Mat src=imread("22.tif");
        imshow("origin",src);
	imwrite("1.jpg",src);
        Mat dst;
    	dst.create(src.rows,src.cols,src.type());
	Fuzzysets(src,dst,11,11);
        imshow("fuzzy",dst);
    	imwrite("fuzzy.jpg",dst);
    	waitKey(0);
    	return 0;
}
void Fuzzysets(Mat& src1,Mat& dst1,int m,int n)
{
	dst1=src1.clone();
	int r=dst1.rows;
	int c=dst1.cols;
	CvScalar sum; 
	for (int i = m / 2;i < r-m / 2;i++){	
		for (int j = n / 2 ;j < c-n / 2;j++){
			sum = 0; 
			for(int k = i - m / 2 ;k < i + m / 2;k++){
				for(int w = j - n / 2 ;w < j + n / 2;w++){
                               		sum.val[0] = sum.val[0] + src1.at<Vec3b>(k,w)[0]; 
					sum.val[1] = sum.val[1] + src1.at<Vec3b>(k,w)[1];
					sum.val[2] = sum.val[2] + src1.at<Vec3b>(k,w)[2];
			}
				}
		dst1.at<Vec3b>(i,j)[0] = sum.val[0] / (m*n);
		dst1.at<Vec3b>(i,j)[1] = sum.val[1] / (m*n);
		dst1.at<Vec3b>(i,j)[2] = sum.val[2] / (m*n);
		}
	}
	
}
