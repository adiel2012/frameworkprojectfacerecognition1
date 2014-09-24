#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"


class MiReconocedorFacial : public core::IFaceRecognitor{
private:
	Ptr<FaceRecognizer> model;
public:
	MiReconocedorFacial(){
		im_width = 77;
        im_height = 77;

	}

	int im_width;
    int im_height;

	virtual void  train(std::vector<cv::Mat> images,std::vector<int> labels){

		int im_width = images[0].cols;
        int im_height = images[0].rows;
		std::vector<cv::Mat> resizedimages;

		
       // cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
		for (int i = 0; i < images.size(); i++)
		{
			Mat face_resized;
			cv::resize(images[i], face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
			resizedimages.push_back(face_resized);
			//imshow( "Display window", face_resized );
			//cvShowImage("Capture", face_resized);
		}

	    model = createFisherFaceRecognizer();
		model->train(resizedimages, labels);	
	}

	virtual  int recognize(cv::Mat* img){

		 return   model->predict(*img);
	}


};