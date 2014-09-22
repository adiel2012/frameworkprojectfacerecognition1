#ifndef _coreh
#define _coreh

#include "opencv2/opencv.hpp"



#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>



namespace core {

	class Rectangle{
	private:
		int x1,y1;
		int x2,y2;
	public:
		int getX1(){return x1;};
		int getY1(){return y1;};
		void setX1(int ax1){ x1=ax1;}
		void setY1(int ay1){ y1=ay1;}
		Rectangle(int ax1, int ay1, int ax2, int ay2){x1=ax1; y1=ay1;x2=ax2; y2=ay2;}
		Rectangle(){}

		int getX2(){return x2;};
		int getY2(){return y2;};
		void setX2(int ax2){ x2=ax2;}
		void setY2(int ay2){ y2=ay2;}
	

	};
	class IFaceRecognitor
	{
	public:
		virtual int  recognize(IplImage* img, Rectangle rectangle) = 0;
	};

	class IFaceDetector{
	public:
		virtual Rectangle*  detect(IplImage*,int& cant) = 0;
	};

	class ClassifiedImage{
		IplImage* img;
		int _class;
	public:
		IplImage* getIimage(){return img;}
		int getclass(){return _class;}
		void setIimage(IplImage* value){ img = value;}
		void setclass(int value){_class=value;}
		ClassifiedImage(){};
		ClassifiedImage(IplImage* aimg,int a_class){img=aimg;_class=a_class;}
	};




	class IClassifiedImageProvider{
	public:
		//ClassifiedImage* getImages()  const;
		IClassifiedImageProvider(){}
		virtual ClassifiedImage*  getImages(int& numimages) = 0;
		//virtual int funcion1() ;
	};










}

#endif