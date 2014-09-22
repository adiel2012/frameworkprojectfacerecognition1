#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"


class MiReconocedorFacial : public core::IFaceRecognitor{
private:
	Ptr<FaceRecognizer> model;
public:
	MiReconocedorFacial(){


	}

	

	virtual void  train(std::vector<cv::Mat> images,std::vector<int> labels){
	    model = createFisherFaceRecognizer();
		model->train(images, labels);	
	}

	virtual  int recognize(cv::Mat* img, core::Rectangle rectangle){

		 return   model->predict(*img);
	}


};