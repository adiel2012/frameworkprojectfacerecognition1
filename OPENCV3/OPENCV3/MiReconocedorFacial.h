#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"

namespace added_namespace{
class MiReconocedorFacial : public core::IFaceRecognitor{
private:
	cv::Ptr<cv::FaceRecognizer> model;
public:
	MiReconocedorFacial():core::IFaceRecognitor(){
		im_width = 77;
        im_height = 77;

	}

	int im_width;
    int im_height;

	virtual void  configure(System::Xml::XmlReader^ config){}

	virtual void  train(std::vector<cv::Mat> images,std::vector<int> labels){

		int im_width = images[0].cols;
        int im_height = images[0].rows;
		std::vector<cv::Mat> resizedimages;

		
       // cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
		for (int i = 0; i < images.size(); i++)
		{
			cv::Mat face_resized;
			cv::resize(images[i], face_resized, cv::Size(im_width, im_height), 1.0, 1.0, cv::INTER_CUBIC);
			resizedimages.push_back(face_resized);
			//imshow( "Display window", face_resized );
			//cvShowImage("Capture", face_resized);
		}

	    model = cv::createFisherFaceRecognizer();
		model->train(resizedimages, labels);	
	}

	virtual  int recognize(cv::Mat* img){

		 return   model->predict(*img);
	}


};

}