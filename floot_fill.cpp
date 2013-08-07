// floot_fill.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"  
#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;
using namespace cv;

typedef  char byte;
byte** CreatImage(byte* image,int width,int height,int bt)
	{
	byte** imageBuf = (byte**)malloc(sizeof(byte*)*(height));
	for(int y=0; y<height; y++)
	{
		
		imageBuf[y] = image+y*width*bt; 
	}
	return imageBuf;
}
bool IsSameColor(byte* c1,byte* c2,int delta)
{
  //cout<<(abs(c1[0]-c2[0])<delta&&abs(c1[1]-c2[1])<delta&&abs(c1[2]-c2[2])<delta);
  return(abs(c1[0]-c2[0])<delta&&abs(c1[0]-c2[0])<delta&&abs(c1[0]-c2[0])<delta);
}

void FillLine(byte** imageBuf,byte** flagBuf,int w,int h,int* pos,byte* fillColor,byte* nowColor,int delta,int* tempStack)
{
  int x=pos[0],y=pos[1];
  //int tempStack[1000][2];
  int stk=0;
  imageBuf[y][x*4]=fillColor[0];
  imageBuf[y][x*4+1]=fillColor[1];
  imageBuf[y][x*4+2]=fillColor[2];
  flagBuf[y][x]=1;
  for(int step=-1;step<2;step+=2)
  {  
 	  x=pos[0]+step;
      y=pos[1];
	  while(x>=0&&x<w)
	  {
		  if (IsSameColor(&imageBuf[y][x*4],nowColor,delta))
		  {
			  imageBuf[y][x*4]=fillColor[0];
			  imageBuf[y][x*4+1]=fillColor[1];
			  imageBuf[y][x*4+2]=fillColor[2];
			  flagBuf[y][x]=1;
			  if(y>0&&imageBuf[y-1][x*4]==0&&IsSameColor(&imageBuf[y-1][x*4],nowColor,delta))
			  {
				  tempStack[stk]=x;
				  tempStack[stk+1]=y-1;
				  stk+=2;
			  }
			  if(y<h-1&&imageBuf[y+1][x*4]==0&&IsSameColor(&imageBuf[y+1][x*4],nowColor,delta))
			  {
				  tempStack[stk]=x;
				  tempStack[stk+1]=y+1;
				  stk+=2;
			  }
			  x+=step;
		  }

		  else
			  break;
	  }
  }
  tempStack[stk]=-1;
}
static byte** FillArea(byte* image,int w,int h,int* pos,byte* color,int delta)
{
	int stack[9999];
	int sk=0;
	byte** imageBuf=CreatImage(image,w,h,4);
	byte* flag=new byte[w*h];
	byte** flagBuf=CreatImage(flag,w,h,1);
	byte nowColor[3];
    int x=pos[0],y=pos[1];
	memset(flag,0,w*h);
	nowColor[0]  =imageBuf[y][x*4];
	cout<<nowColor[0];
	nowColor[1]  =imageBuf[y][x*4+1];
	//cout<<nowColor[1];
	nowColor[2]  =imageBuf[y][x*4+2];
	//cout<<nowColor[2];
	stack[sk]=x;
    stack[sk+1]=y+1;
    sk+=2;
	while(sk>0)
	{
		
		sk-=2;
		int* tempStack=new int[9999];
		int* pos=new int[2];
		pos[0]=stack[sk];
		pos[1]=stack[sk+1];
		FillLine(imageBuf,flagBuf,w,h,pos,color,nowColor,delta,tempStack);
		int k=0,i;

		for(i=2;i<sk;i+=2)
		{
			x=stack[i];
			y=stack[i+1];
		
			if(flagBuf[y][x]==0)
			{
				stack[k]=stack[i];
				stack[k+1]=stack[i+1];
				k+=2;
			}
		}
		sk=k;
		
		i=0;
		while(tempStack[i]!=-1)
		{
			stack[sk]=tempStack[i];
			stack[sk+1]=tempStack[i+1];
			sk+=2;
			i+=2;
		}
	}
	return imageBuf ;
	free(imageBuf);
	free(flagBuf);
	delete[] flag;

}
int main(int argc,char ** argv)    
{    
 byte*  fillColor=new byte[3];
 fillColor[0]=255;
 fillColor[1]=0;
 fillColor[2]=0;
 int *pos=new int[2];
 pos[0]=1;
 pos[1]=1;
 IplImage* face = cvLoadImage("F:\\myproject\\picture\\lena.jpg",CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);   
 char** imageBuf=FillArea(face->imageData,face->width,face->height,pos,fillColor,1000);
 //char** imageBuf=(char**)CreatImage(face->imageData,face->width,face->height,3);
 IplImage* img = cvCreateImage(cvGetSize(face) ,face->depth,3 );
 
 img->imageData = (char*)imageBuf[0]; 
 cvNamedWindow( "Image",1 );
 cvShowImage( "Image", img );

 cvWaitKey() ;


  return 0;

}  

