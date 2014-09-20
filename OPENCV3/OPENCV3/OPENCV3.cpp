// OPENCV3.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "opencv2/opencv.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>


//#include "core.h";
#include "core_experiment.h";
#include "opencv_core.h";

//#include "allcore.h";

#include "MiDetector.h";
#include "MiReconocedorFacial.h";
#include "AttfacesImgProvider.h";

using namespace System;



int main1();
int adielsample();
int main(array<System::String ^> ^args)
{



    Console::WriteLine(L"Hola a todos");
	return adielsample();

   // return main1();
}



int adielsample(){

	// esto debe hacerse con un inyector de dependencias
	core::IFaceDetector* detector =  new MiDetector();
	core::IFaceRecognitor* recog =  new MiReconocedorFacial();
	core::IClassifiedImageProvoder* imgprovider =  new AttfacesImageProvider();

	imgprovider->getImages();
	return 0;

	core_experiment::IExperimenter* experiment = new core_experiment::TenfoldCrossValidation(detector,recog,imgprovider);
	float* results = experiment->getResults();

	for (int i = 0; i < sizeof(results); i++)
	{
		Console::WriteLine(results[i]);
	}

	delete detector;
	delete recog;
	delete imgprovider;
	delete [] results;

	return -1;
}

int main1()
{
	IplImage* img = cvLoadImage("C:/lena.png");


	if (!img)
		printf("Image can NOT Load!!!\n");
	
	
	int i, c;
	IplImage *src_img = img, *src_gray = 0;
	cv::Mat mat =  cv::Mat(src_img, true);
	const char *cascade_name = "D://Adiel/ECUADOR/INVESTIGACION/OPENCV/FRAMEWORK/opencv6/Debug/haarcascade_frontalface_default.xml";
	CvHaarClassifierCascade *cascade = 0;
	CvMemStorage *storage = 0;
	CvSeq *faces;
	cascade = (CvHaarClassifierCascade *) cvLoad (cascade_name, 0, 0, 0);
	//cvNamedWindow ("Capture", CV_WINDOW_AUTOSIZE);
	//CvCapture *capture = cvCreateCameraCapture(0);

	src_gray = cvCreateImage (cvGetSize(src_img), IPL_DEPTH_8U, 1);
		storage = cvCreateMemStorage (0);
		cvClearMemStorage (storage);
		cvCvtColor (src_img, src_gray, CV_BGR2GRAY);
		cvEqualizeHist (src_gray, src_gray);
		faces = cvHaarDetectObjects (src_gray, cascade, storage,1.11, 4, 0, cvSize (40, 40));
		
		for (i = 0; i < (faces ? faces->total : 0); i++) {
			CvRect *r = (CvRect *) cvGetSeqElem (faces, i);

			cv::rectangle(  mat,*r, cv::Scalar(100, 100, 200));
			//doMosaic(src_img, r->x, r->y, r->width, r->height, 20);
		}
		
		imshow( "Display window", mat );
		//cvShowImage("Capture", src_img);
		cvReleaseImage(&src_gray);
		c = cvWaitKey(0);

	
	
	
	
	
	/*cvNamedWindow("myfirstwindow");
	cvShowImage("myfirstwindow", img);

	cvWaitKey(0);
	cvReleaseImage(&img);*/

	return 0;
}

