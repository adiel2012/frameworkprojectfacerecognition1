#ifndef _coreh
#define _coreh

#include "opencv2/opencv.hpp"



#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>



namespace core {

	class Rectangle{
	private:
		int x,y;
	public:
		int getX(){return x;};
		int getY(){return y;};
		void setX(int ax){ x=ax;}
		void setY(int ay){ y=ay;}
		Rectangle(int ax, int ay){x=ax; y=ay;}

	};
	class IFaceRecognitor
	{
	public:
		virtual int  recognize(IplImage* img, Rectangle rectangle) = 0;
	};

	class IFaceDetector{
	public:
		virtual Rectangle*  detect(IplImage*) = 0;
	};

	class ClassifiedImage{
		IplImage* img;
		int _class;
	public:
		IplImage* getIimage(){return img;}
		int getclass(){return _class;}
		void setIimage(IplImage* value){ img = value;}
		void setclass(int value){_class=value;}
		ClassifiedImage(IplImage* aimg,int a_class){img=aimg;_class=a_class;}
	};




	class IClassifiedImageProvider{
	public:
		//ClassifiedImage* getImages()  const;
		IClassifiedImageProvider(){}
		virtual ClassifiedImage*  getImages() = 0;
		//virtual int funcion1() ;
	};










}

#endif