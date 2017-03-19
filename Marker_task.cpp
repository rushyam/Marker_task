#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "iostream"
using namespace cv;
using namespace std;
int  dis(Point p1,Point p2);
int main()
{
  VideoCapture vid("auvd1.avi");
  char ch;
  namedWindow("track_bar");
  int vmin=70,hmin=0,smin=70,hmax=10,smax=255,vmax=255;
  createTrackbar("vmin","track_bar",&vmin,255);
  createTrackbar("vmam","track_bar",&vmax,255);
  createTrackbar("hmin","track_bar",&hmin,255);
  createTrackbar("hmax","track_bar",&hmax,255);
  createTrackbar("smin","track_bar",&smin,255);
  createTrackbar("smax","track_bar",&smax,255);


  while(ch=' ')
    {
      int x1,x2,x3,x4,y1,y2,y3,y4;
      Mat img;
      vid.read(img);
      Mat hsv(img.rows,img.cols,CV_8UC3);
      Mat imgb(img.rows,img.cols,CV_8UC1,Scalar(0));
      Mat imgc(img.rows,img.cols,CV_8UC1,Scalar(0));
      Mat imgc1(img.rows,img.cols,CV_8UC1,Scalar(0));
      Mat imgc2(img.rows,img.cols,CV_8UC1,Scalar(0));
      cvtColor(img,hsv,CV_BGR2HSV);
      inRange(hsv, Scalar(hmin,smin,vmin), Scalar(hmax, smax, vmax),imgb);
      


       int f=0,i,j;
       for(i=1;i<img.rows-1;i++)
       	 {
       	   for(j=1;j<img.cols-1;j++)
       	     {
	       imgc1.at<uchar>(i,j)=imgb.at<uchar>(i,j);
       	       int c=0;
       	       for(int a=-1;a<2;a++)
       		 {
       		   for(int b=-1;b<2;b++)
       		     {
		       if(a==0&&b==0)
			 continue;
       		       if(imgb.at<uchar>(i+a,j+b)==0&&imgb.at<uchar>(i,j)==255)
       			 c++;
       		     }
       		 }
       	       if(c>=4)
       		 imgc1.at<uchar>(i,j)=0;
	     }
	 }
       for(i=1;i<img.rows-1;i++)
       	 {
       	   for(j=1;j<img.cols-1;j++)
       	     {
	       imgc2.at<uchar>(i,j)=imgc1.at<uchar>(i,j);
       	       int c=0;
       	       for(int a=-1;a<2;a++)
       		 {
       		   for(int b=-1;b<2;b++)
       		     {
		       if(a==0&&b==0)
			 continue;
       		       if(imgc1.at<uchar>(i+a,j+b)==255&&imgc1.at<uchar>(i,j)==0)
       			 c++;
       		     }
       		 }
       	       if(c>=1)
       		 imgc2.at<uchar>(i,j)=255;
	     }
	 }

 for(i=1;i<img.rows-1;i++)
       	 {
       	   for(j=1;j<img.cols-1;j++)
       	     {
	       imgc.at<uchar>(i,j)=imgc2.at<uchar>(i,j);
       	       int c=0;
       	       for(int a=-1;a<2;a++)
       		 {
       		   for(int b=-1;b<2;b++)
       		     {
		       if(a==0&&b==0)
			 continue;
       		       if(imgc2.at<uchar>(i+a,j+b)==255&&imgc2.at<uchar>(i,j)==0)
       			 c++;
       		     }
       		 }
       	       if(c>=1)
       		 imgc.at<uchar>(i,j)=255;
	     }
	 }
      
       imshow("rawg",imgc);

       for(i=0;i<img.rows;i++)
       	 {
       	   for(j=0;j<img.cols;j++)
       	     {
       	       if(imgc.at<uchar>(i,j)==255)
       		 {
       		   f=1;
       		   break;
       		 }
       	     }
       	   if(f==1)
       	     break;
       	 }
       x1=j;
       y1=i;

       for(i=img.rows-1;i>-1;i--)
       	 {f=0;
       	   for(j=0;j<img.cols;j++)
       	     {
       	       if(imgc.at<uchar>(i,j)==255)
       		 {
       		   f=1;
       		   break;
       		 }
       	     }
       	   if(f==1)
       	     break;
       	 }
       x2=j;
       y2=i;
       for(i=0;i<img.rows;i++)
       	 {f=0;
       	   for(j=img.cols-1;j>-1;j--)
       	     {
       	       if(imgc.at<uchar>(i,j)==255)
       		 {
       		   f=1;
       		   break;
       		 }
       	     }
       	   if(f==1)
       	     break;
       	 }
       x4=j;
       y4=i;
  
       for(i=img.rows-1;i>-1;i--)
       	 {f=0;
       	   for(j=img.cols-1;j>-1;j--)
       	     {
       	       if(imgc.at<uchar>(i,j)==255)
       		 {
       		   f=1;
       		   break;
       		 }
       	     }
       	   if(f==1)
       	     break;
       	 }
       x3=j;
       y3=i;
      
       Point pt[4];
       pt[0].x=x1;
       pt[1].x=x2;
       pt[2].x=x3;
       pt[3].x=x4;
       pt[0].y=y1;
       pt[1].y=y2;
       pt[2].y=y3;
       pt[3].y=y4;
       int d[4];
       d[0]=dis(pt[0],pt[1]);
       d[1]=dis(pt[1],pt[2]);
       d[2]=dis(pt[2],pt[3]);
       d[3]=dis(pt[3],pt[0]);
       for(i=0;i<4;)
	 {
	   int k=0;
	   for(j=0;j<4;j++)
	     {
	       if(d[i]<d[j])
		 k++;
	     }
	   if(k==0)
	     break;
	   i++;
	 }
       line(img,pt[0],pt[1],(0,0,0),4);
       line(img,pt[1],pt[2],(0,0,0),3);
       line(img,pt[2],pt[3],(0,0,0),3);
       line(img,pt[3],pt[0],(0,0,0),3);
       if(i<3)
        line(img,pt[i],pt[i+1],(255),4);
       if(i==3)
	 line(img,pt[i],pt[0],(255),4); 
       imshow("video",img);
    ch= waitKey(0);
    }

  return 0;
}
int dis(Point p1,Point p2)
{
  float d=(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
  return d;
}
