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
		virtual int  recognize(cv::Mat* img, Rectangle rectangle) = 0;
		virtual void  train(std::vector<cv::Mat> images,std::vector<int> labels) = 0;
	};

	class IFaceDetector{
	public:
		virtual cv::Mat*  detect(IplImage* img,int& cant) = 0;
	};

	class ClassifiedImage{
		cv::Mat* img;
		int _class;
	public:
		cv::Mat* getIimage(){return img;}
		int getclass(){return _class;}
		void setIimage(cv::Mat* value){ img = value;}
		void setclass(int value){_class=value;}
		ClassifiedImage(){};
		ClassifiedImage(cv::Mat* aimg,int a_class){img=aimg;_class=a_class;}
	};




	class IClassifiedFaceProvider{
	public:
		//ClassifiedImage* getImages()  const;
		IClassifiedFaceProvider(){}
		virtual ClassifiedImage*  getImages(int& numimages, core::IFaceDetector* adetector) = 0;
		//virtual int funcion1() ;
	};










}

#endif