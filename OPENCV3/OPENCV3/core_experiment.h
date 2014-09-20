#ifndef _coreh
#include "core.h"
#endif


#ifndef _core_experimenth
#define _core_experimenth

using namespace core;

namespace core_experiment {
	//--------------------------------------------------------------------------------------------------
	class IExperimenter{
	
	protected:
		core::IFaceDetector* _detector;
		core::IFaceRecognitor* _recognitor;
		core::IClassifiedImageProvoder* _imgprovider;
	public :
		float* getResults() const;
		 

		IExperimenter (core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvoder* aimgprovider){
		_detector = adetector;
		_recognitor = arecognitor;
		_imgprovider = aimgprovider;
		}
	};
	//--------------------------------------------------------------------------------------------------------

	class TenfoldCrossValidation: public IExperimenter{
	public:
		TenfoldCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvoder* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		float* getResults() {

			std::vector<int> classes;
			std::vector<core::Rectangle> faces;
			std::vector<IplImage*> images;

			core::ClassifiedImage* imgs = this->_imgprovider->getImages();//  _imgprovider->getImages();
			int cantimg = sizeof( imgs );
			for (int i = 0; i < cantimg; i++)
			{
				
				core::Rectangle* rects = _detector->detect(imgs[i].getIimage());
				images.push_back(imgs[i].getIimage());
			    int cantimg = sizeof( rects );
				if(cantimg!=1)
				{
					// ver que se hace sui la cantidad de caras es distinto de 1
				}
				classes.push_back(imgs[i].getclass());
				faces.push_back(rects[0]);
			}

			// ordenar por clases
			for (int i = 0; i < cantimg-1; i++)
			{
				for (int j = i+1; j < cantimg; j++)
				{
					if(classes.at(i)>classes.at(j)){
					
						/*classes.swap(i,j);
						faces.swap(i,j);
						images.swap(i,j);*/
					}
				}
			}

			

			return nullptr;
		}
	};

	class HoldOutCrossValidation: public IExperimenter{
	public:
		HoldOutCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvoder* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		float* getResults() {
		

			return nullptr;
		}
	};
}
#endif