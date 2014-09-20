#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"


class MiReconocedorFacial : public core::IFaceRecognitor{
private:

public:
	MiReconocedorFacial(){
	  
	
	}

	virtual  int recognize(IplImage* img, core::Rectangle rectangle){
	   return -1;
	}


};