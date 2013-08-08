// floot_fill.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"  
#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;
using namespace cv;

#define  M 50

bool IsSameColor(CvScalar c1,CvScalar c2,int delta)
{
 // cout<<(abs(c1.val[0]-c2.val[0])<delta&&abs(c1.val[1]-c2.val[1])<delta&&abs(c1.val[2]-c2.val[2])<delta)<<endl;
  return(abs(c1.val[0]-c2.val[0])<delta&&abs(c1.val[1]-c2.val[1])<delta&&abs(c1.val[2]-c2.val[2])<delta);
}


void flood_fill (IplImage* image,int row_size, int col_size,int x, int y,  CvScalar oldColor,CvScalar newColor)
{
	
	if(!IsSameColor(oldColor,cvGet2D(image,x,y),M))
		return;
	int y1=y;
	while(y1<row_size&&IsSameColor(oldColor,cvGet2D(image,x,y1),M))//bottom
	{
	   cvSet2D(image,x,y1,newColor);
	   CvScalar Color=cvGet2D(image,x,y1);
	   cout<<x<<" "<<y1<<endl;
	   cout<<Color.val[0]<<" "<<Color.val[1]<<" "<<Color.val[2]<<endl;
	   y1++;
	   
	}
    y1 = y - 1;
    while(y1 >= 0 && IsSameColor(oldColor,cvGet2D(image,x,y1),M))//top
    {
            cvSet2D(image,x,y1,newColor);
	    CvScalar Color=cvGet2D(image,x,y1);
	    cout<<x<<" "<<y1<<endl;
	    cout<<Color.val[0]<<" "<<Color.val[1]<<" "<<Color.val[2]<<endl;
        y1--;
    }
	 y1 = y;
    while(y1 <row_size && IsSameColor(newColor,cvGet2D(image,x,y1),M))//left
    {
        if(x >0 &&IsSameColor(oldColor,cvGet2D(image,x-1,y1),M)) 
        {
            flood_fill(image, row_size, col_size,x-1, y1, oldColor,newColor);
        } 
        y1++;
    }
    y1 = y - 1;
    while(y1 >= 0 && IsSameColor(newColor,cvGet2D(image,x,y1),M))
    {
        if(x >0 &&IsSameColor(oldColor,cvGet2D(image,x-1,y1),M)) 
        {
           flood_fill(image, row_size, col_size,x-1, y1, oldColor,newColor);
        }
        y1--;
    } 
    
	y1 = y;
    while(y1 <row_size &&IsSameColor(newColor,cvGet2D(image,x,y1),M))//right
    {
        if(x < col_size - 1 &&IsSameColor(oldColor,cvGet2D(image,x+1,y1),M)) 
        {           
             flood_fill(image, row_size, col_size,x+1, y1, oldColor,newColor);
        } 
        y1++;
    }
    y1 = y - 1;
    while(y1 >= 0 && IsSameColor(newColor,cvGet2D(image,x,y1),M))
    {
        if(x < col_size - 1 && IsSameColor(oldColor,cvGet2D(image,x+1,y1),M)) 
        {
            flood_fill(image, row_size, col_size,x+1, y1, oldColor,newColor);
        }
        y1--;
    }
	return;
}
	
 
int main(int argc,char ** argv)    
{  
	IplImage* face = cvLoadImage("F:\\myproject\\picture\\2.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);  
	CvScalar newColor=CV_RGB(255,0,0);
	cout<<"new"<<newColor.val[0]<<" "<<newColor.val[1]<<" "<<newColor.val[2]<<endl;
	CvScalar oldColor=cvGet2D(face,20,20);
	cout<<"old"<<oldColor.val[0]<<" "<<oldColor.val[1]<<" "<<oldColor.val[2]<<endl;
	flood_fill(face,face->width,face->height,50,50,oldColor, newColor);
	cvNamedWindow( "Image",1 );
	cvShowImage( "Image", face );
	cvWaitKey() ;
	return 0;

}  

