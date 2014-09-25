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
		virtual int  recognize(cv::Mat* img) = 0;
		virtual void  train(std::vector<cv::Mat> images,std::vector<int> labels) = 0;
		virtual void  configure(System::Xml::XmlReader^ config) = 0;
	};

	class IFaceDetector{
	public:
		virtual cv::Mat*  detect(cv::Mat img,int& cant, std::vector<cv::Rect> rectangles) = 0;
		virtual void  configure(System::Xml::XmlReader^ config) = 0;
	};

	class ClassifiedImage{
		cv::Mat img;
		int _class;
	public:
		cv::Mat getIimage(){return img;}
		int getclass(){return _class;}
		void setIimage(cv::Mat value){ img = value;}
		void setclass(int value){_class=value;}
		ClassifiedImage(){};
		ClassifiedImage(cv::Mat aimg,int a_class){img=aimg;_class=a_class;}
	};




	class IClassifiedFaceProvider{
	public:
		//ClassifiedImage* getImages()  const;
		IClassifiedFaceProvider(){}
		virtual ClassifiedImage*  getImages(int& numimages, core::IFaceDetector* adetector) = 0;
		virtual void  configure(System::Xml::XmlReader^ config) = 0;
		//virtual int funcion1() ;
	};





	class VideoDetector{
	private:

	public:
		void run (IFaceDetector* detector){


			// Get the path to your CSV:
			//			string fn_haar = string("");
			//			string fn_csv = string("");
			int deviceId = atoi("");
			// These vectors hold the images and corresponding labels:
			//std::vector<cv::Mat> images;
			//std::vector<int> labels;
			/*    // Read in the data (fails if no valid input filename is given, but you'll get an error message):
			try {
			read_csv(fn_csv, images, labels);
			} catch (cv::Exception& e) {
			cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
			// nothing more we can do
			exit(1);
			}*/
			// Get the height from the first image. We'll need this
			// later in code to reshape the images to their original
			// size AND we need to reshape incoming faces to this size:
			//int im_width = images[0].cols;
			//int im_height = images[0].rows;


			// That's it for learning the Face Recognition model. You now
			// need to create the classifier for the task of Face Detection.
			// We are going to use the haar cascade you have specified in the
			// command line arguments:
			//
			//cv::CascadeClassifier haar_cascade;
			//haar_cascade.load("");
			// Get a handle to the Video device:
			cv::VideoCapture cap(deviceId);
			// Check if we can use this device at all:
			if(!cap.isOpened()) {
				//cerr << "Capture Device ID " << deviceId << "cannot be opened." << endl;
				//return -1;
			}
			// Holds the current frame from the Video device:
			cv::Mat frame;
			for(;;) {
				cap >> frame;
				cv::Mat original = frame.clone();
				int cant;
				std::vector<cv::Rect> rectangles;
				cv:: Mat* matrices = detector->detect(frame,cant,rectangles);

				for (int i = 0; i < rectangles.size(); i++)
				{
					cv::rectangle  (original,rectangles[i], cv::Scalar(100, 100, 200));
				}

				imshow("face_recognizer", original);
			}
			// Show the result:
			
			// And display it:
			//char key = (char) waitKey(20);

		}

	};




}

#endif