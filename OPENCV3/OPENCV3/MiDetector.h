#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"

using namespace System;
			using namespace System::IO;
			using namespace System::Runtime::InteropServices;

class MiDetector : public core::IFaceDetector{
private:

public:
	MiDetector(){


	}

	virtual cv::Mat* detect(IplImage* img, int& cant){

		std::vector<cv::Mat> rectangulos; 

		//IplImage* img = cvLoadImage("C:/lena.png");


		if (!img)
			printf("Image can NOT Load!!!\n");


		int i, c;
		IplImage *src_img = img, *src_gray = 0;
		cv::Mat mat =  cv::Mat(src_img, true);


		
		/*	String^ folder =   Directory::GetCurrentDirectory()+"\\datasets\\att_faces";*/

		const char *cascade_name =   (char*)Marshal::StringToHGlobalAnsi(Directory::GetCurrentDirectory()+"\\haarcascade_frontalface_default.xml").ToPointer()   ;
		CvHaarClassifierCascade *cascade = 0;
		CvMemStorage *storage = 0;
		CvSeq *faces;
		cascade = (CvHaarClassifierCascade *) cvLoad (cascade_name, 0, 0, 0);

		src_gray = cvCreateImage (cvGetSize(src_img), IPL_DEPTH_8U, 1);
		storage = cvCreateMemStorage (0);
		cvClearMemStorage (storage);
		cvCvtColor (src_img, src_gray, CV_BGR2GRAY);
		cvEqualizeHist (src_gray, src_gray);
		faces = cvHaarDetectObjects (src_gray, cascade, storage,1.11, 4, 0, cvSize (55, 55));
		
		for (i = 0; i < (faces ? faces->total : 0); i++) {
			CvRect *r = (CvRect *) cvGetSeqElem (faces, i);
			cv::Mat face =  cv::Mat(src_gray,r);

			rectangulos.push_back(face);

			//rectangulos.push_back(new core::Rectangle(r->x,r->y,r->x+r->width,r->y+r->height));
			//rectangulos.push_back(new core::Rectangle(r->x,r->y,r->x+r->width,r->y+r->height));
			//cv::rectangle(  mat,*r, cv::Scalar(100, 100, 200));
			//doMosaic(src_img, r->x, r->y, r->width, r->height, 20);
		}

		cant = rectangulos.size();
		cv::Mat* res = new cv::Mat[cant];
		for (int i = 0; i < cant; i++)
		{
			res[i] = rectangulos[i] ;
		}
		
		
		return res;
	}
};