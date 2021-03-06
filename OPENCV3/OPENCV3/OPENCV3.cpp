// OPENCV3.cpp: archivo de proyecto principal.

#include "stdafx.h"
#include "opencv2/opencv.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;



//#include "config.h"

#include "core_experiment.h"
//#include "temp.h"

/*
#include "allcore_gc.h"
#include "MiDetector2_gc.h"
#include "MiDetector2_gc.h"
#include "MiReconocedorFacial_gc.h"
#include "AttImgProvider.h"

*/



int main1();
int adielsample();
int adielsample2();
int mainvideo();


int main(array<System::String ^> ^args)
{



	System::Console::WriteLine(L"Hola a todos");
	//return adielsample2();
	return mainvideo();
	// return main1();
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

	//imshow( "Display window", mat );
	//cvShowImage("Capture", src_img);
	cvReleaseImage(&src_gray);
	c = cvWaitKey(0);






	/*cvNamedWindow("myfirstwindow");
	cvShowImage("myfirstwindow", img);

	cvWaitKey(0);
	cvReleaseImage(&img);*/

	return 0;
}

int adielsample(){

	// esto debe hacerse con un inyector de dependencias
	core::IFaceDetector* detector =  new added_namespace::MiDetector2();
	core::IFaceRecognitor* recog =  new added_namespace::MiReconocedorFacial();
	core::IClassifiedFaceProvider* imgprovider =  new providers::AttImgProvider();

	int cantimgs = -1;
	//imgprovider->getImages(cantimgs,detector);




	core_experiment::IExperimenter* experiment = new core_experiment::TenfoldCrossValidation(detector,recog,imgprovider);
	int cant=0;
	float* trainingresults;
	float* results = experiment->getResults(cant,trainingresults);

	for (int i = 0; i < cantimgs; i++)
	{
		System::Console::WriteLine(results[i]);
	}

	delete detector;
	delete recog;
	delete imgprovider;
	delete [] results;

	System::Console::ReadLine();
	return 0;
}

int adielsample2(){

/*	System::Object^ objeto = System::Activator::CreateInstance(System::Type::GetType("System.EventArgs"));
	System::Runtime::InteropServices::GCHandle handle = System::Runtime::InteropServices::GCHandle::Alloc(objeto);
	System::IntPtr pointer = System::Runtime::InteropServices::GCHandle::ToIntPtr(handle);			
	System::EventArgs* reconocedor = (System::EventArgs*)(pointer.ToPointer());  */


	core_experiment::XmlRunner* experimento = new core_experiment::XmlRunner();
	experimento->run();

	// esto debe hacerse con un inyector de dependencias
	System::Console::ReadLine();
	return 0;
}

int mainvideo()
{
	//create the cascade classifier object used for the face detection
	CascadeClassifier face_cascade;
	//use the haarcascade_frontalface_alt.xml library
	face_cascade.load("haarcascade_frontalface_alt.xml");

	//setup video capture device and link it to the first capture device
	VideoCapture captureDevice;

	
	//CV_CAP_ANY
	int deviceId = atoi("FaceCam 300");
	captureDevice.open(deviceId);

	//setup image files used in the capture process
	Mat captureFrame;
	Mat grayscaleFrame;

	//create a window to present the results
	namedWindow("outputCapture", 1);

	//create a loop to capture and find faces
	while(true)
	{
		//capture a new image frame
		captureDevice>>captureFrame;

		//convert captured image to gray scale and equalize
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		//create a vector array to store the face found
		std::vector<Rect> faces;

		//find faces and store them in the vector array
		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));

		//draw a rectangle for all found faces in the vector array on the original image
		for(int i = 0; i < faces.size(); i++)
		{
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
		}

		//print the output
		imshow("outputCapture", captureFrame);

		//pause for 33ms
		waitKey(33);
	}


	return 0;
}



