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
		int recognize(IplImage* img, Rectangle rectangle) const;
	};

	class IFaceDetector{
	public:
		Rectangle* detect(IplImage*) const;
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

	class IClassifiedImageProvoder{
	public:
		ClassifiedImage* getImages() {return nullptr;};
		IClassifiedImageProvoder(){}
	};

}

#endif