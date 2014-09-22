#ifndef _coreh
#include "core.h"
#endif


#ifndef _core_experimenth
#define _core_experimenth



namespace core_experiment {
	//--------------------------------------------------------------------------------------------------
	class IExperimenter{

	protected:
		core::IFaceDetector* _detector;
		core::IFaceRecognitor* _recognitor;
		core::IClassifiedFaceProvider* _imgprovider;
	public :
		virtual float* getResults() = 0;


		IExperimenter (core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider){
			_detector = adetector;
			_recognitor = arecognitor;
			_imgprovider = aimgprovider;
		}
	};
	//--------------------------------------------------------------------------------------------------------

	class TenfoldCrossValidation: public IExperimenter{
	public:
		TenfoldCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {

			


			int g = 0;
			int cantimg = -1;
			core::ClassifiedImage* imgs = this->_imgprovider->getImages(cantimg,_detector);//  _imgprovider->getImages();
			std::vector<cv::Mat> faces;
			std::vector<int> labels;

			for (int i = 0; i < cantimg; i++)
			{
				faces.push_back(*(imgs[i].getIimage()));
				labels.push_back(imgs[i].getclass());
			}

			_recognitor->train(faces,labels);

			// ordenar por clases
			/*for (int i = 0; i < cantimg-1; i++)
			{
				for (int j = i+1; j < cantimg; j++)
				{
					if(classes.at(i)>classes.at(j)){


					}
				}
			}*/



			return nullptr;
		}
	};

	class HoldOutCrossValidation: public IExperimenter{
	public:
		HoldOutCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {


			return nullptr;
		}
	};
}
#endif