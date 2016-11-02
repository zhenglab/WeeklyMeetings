#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;  
using namespace cv;
int main()
{  

	
	Mat srcimage = imread("11.tif");  
	imshow("原始图像",srcimage);  
        imwrite("原始图像.jpg",srcimage);
	//按原始图的参数规格来创建创建效果图
	Mat dstimage;
	dstimage.create(srcimage.rows,srcimage.cols,srcimage.type());//效果图的大小、类型与原图片相同 
	Mat dstimage2;
	dstimage2.create(srcimage.rows,srcimage.cols,srcimage.type());
        Mat dstimage3;
	dstimage3.create(srcimage.rows,srcimage.cols,srcimage.type());
	int r = srcimage.rows;  //行数
	int c = srcimage.cols;  //列数
	for(int i = 0;i < r;i++){  
		for(int j = 0;j < c;j++){  	
			dstimage.at<Vec3b>(i,j)[0] = 255-srcimage.at<Vec3b>(i,j)[0] ;  //蓝色通道
			dstimage.at<Vec3b>(i,j)[1] = 255-srcimage.at<Vec3b>(i,j)[1] ;  //绿色通道
			dstimage.at<Vec3b>(i,j)[2] = 255-srcimage.at<Vec3b>(i,j)[2];  //红是通道
			
		}       
	} 
        imshow("xiaogutu",dstimage);
        imwrite("xiaogutu.jpg",dstimage); 
        CvScalar  sum; 
        sum=0;                                      
        for(int x = 0;x < r;x++){
        	for(int y = 0;y < c;y++){
                                                                  
                	sum.val[0] = sum.val[0] + srcimage.at<Vec3b>(x,y)[0]; //蓝色通道求和；
               
                    	sum.val[1] = sum.val[1] + srcimage.at<Vec3b>(x,y)[1]; //绿色通道求和；
                
                    	sum.val[2] = sum.val[2] + srcimage.at<Vec3b>(x,y)[2]; //红色通道求和；
                
               
              	}
      	} 
    	 for(int k = 0;k < r;k++){
              	for(int w = 0;w < c;w++)                                          
             {     
                dstimage2.at<Vec3b>(k,w)[0] = 3*(sum.val[0]/(r*c));          
                dstimage2.at<Vec3b>(k,w)[1] = 3*(sum.val[1]/(r*c));          
                dstimage2.at<Vec3b>(k,w)[2] = 3*(sum.val[2]/(r*c));          

              }
           }
         imshow("pingjun",dstimage2);
         imwrite("pingjun.jpg",dstimage2); 
         for(int m = 0;m < r;m++){
         	for(int n = 0;n < c;n++){                      
                 	if(dstimage2.at<Vec3b>(m,n)[0] >=srcimage.at<Vec3b>(m,n)[0])
                 	dstimage3.at<Vec3b>(m,n)[0] = dstimage2.at<Vec3b>(m,n)[0];
                 	else 
                	dstimage3.at<Vec3b>(m,n)[0]  = srcimage.at<Vec3b>(m,n)[0];
                 	if(dstimage2.at<Vec3b>(m,n)[1] >=srcimage.at<Vec3b>(m,n)[1])
                 	dstimage3.at<Vec3b>(m,n)[1] = dstimage2.at<Vec3b>(m,n)[1];
                 	else 
                	dstimage3.at<Vec3b>(m,n)[1] = srcimage.at<Vec3b>(m,n)[1];
                 	if(dstimage2.at<Vec3b>(m,n)[2] >=srcimage.at<Vec3b>(m,n)[2])
                 	dstimage3.at<Vec3b>(m,n)[2] = dstimage2.at<Vec3b>(m,n)[2];
                	else 
                 	dstimage3.at<Vec3b>(m,n)[2] = srcimage.at<Vec3b>(m,n)[2];
                 
        	 }
         }
         imshow("bingji",dstimage3);
         imwrite("bingji.jpg",dstimage3); 
	 waitKey(0); 
         return 0;  
}  
