#include "core.h"
#include "core_experiment.h"
#include "opencv_core.h"


class MiDetector : public core::IFaceDetector{
private:

public:
	MiDetector(){
	  
	
	}

	virtual core::Rectangle* detect(IplImage*){
		return nullptr;
	}
};