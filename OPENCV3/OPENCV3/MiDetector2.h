#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include <iostream>
//#include <stdio.h>

using namespace std;
using namespace cv;

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

class MiDetector2 : public core::IFaceDetector{
private:



public:
	MiDetector2(){


	}





	virtual cv::Mat* detect(IplImage* img, int& cant){




		std::vector<cv::Mat> rectangulos; 
		if (!img)
			printf("Image can NOT Load!!!\n");


		cv::Mat frame =  cv::Mat(img, true);
		//IplImage*frame= img;


		//cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
		//cv::String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
		CascadeClassifier face_cascade;
		CascadeClassifier eyes_cascade;
		string window_name = "Capture - Face detection";
		RNG rng(12345);
		if( !face_cascade.load( (char*)Marshal::StringToHGlobalAnsi(System::IO::Directory::GetCurrentDirectory()+"\\haarcascade_frontalface_alt.xml").ToPointer() ) ){ 
			printf("--(!)Error loading\n"); };
		if( !eyes_cascade.load( (char*)Marshal::StringToHGlobalAnsi(System::IO::Directory::GetCurrentDirectory()+"\\haarcascade_eye_tree_eyeglasses.xml").ToPointer() )  ) { 
			printf("--(!)Error loading\n"); };


		std::vector<Rect> faces;
		Mat frame_gray;

		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		equalizeHist( frame_gray, frame_gray );

		//-- Detect faces
		face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

		for( size_t i = 0; i < faces.size(); i++ )
		{
			Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );

			
			//rectangulos.push_back(new core::Rectangle(faces[i].x,faces[i].y,faces[i].x+faces[i].width,faces[i].y+faces[i].height));

			//CvRect *r = faces[i];
			cv::Mat face =  cv::Mat(frame_gray,faces[i]);

			rectangulos.push_back(face);

			//ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

			//  FALTA ALINEAR  CON LO DE LOS OJOS
			Mat faceROI = frame_gray( faces[i] );
			std::vector<Rect> eyes;

			//-- In each face, detect eyes
			eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );


			




			/*for( size_t j = 0; j < eyes.size(); j++ )
			{
				Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
				int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
				circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
			}*/
		}
		//-- Show what you got
		//imshow( window_name, frame );



		//------------------------------












		cant = rectangulos.size();
		cv::Mat* res = new cv::Mat[cant];
		for (int i = 0; i < cant; i++)
		{
			res[i] = rectangulos[i] ;
		}
		
		return res;
	}
};