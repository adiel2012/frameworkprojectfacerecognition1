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
		core::IClassifiedImageProvider* _imgprovider;
	public :
		virtual float* getResults() = 0;


		IExperimenter (core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvider* aimgprovider){
			_detector = adetector;
			_recognitor = arecognitor;
			_imgprovider = aimgprovider;
		}
	};
	//--------------------------------------------------------------------------------------------------------

	class TenfoldCrossValidation: public IExperimenter{
	public:
		TenfoldCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {

			std::vector<int> classes;
			std::vector<core::Rectangle> faces;
			std::vector<IplImage*> images;


			int g = 0;
			int cantimg = -1;
			core::ClassifiedImage* imgs = this->_imgprovider->getImages(cantimg);//  _imgprovider->getImages();

			for (int i = 0; i < cantimg; i++)
			{
				int cantrect = -1;
				core::Rectangle* rects = _detector->detect(imgs[i].getIimage(),cantrect);
				System::Console::WriteLine(i);

				if(cantrect!=1)
				{
					// ver que se hace sui la cantidad de caras es distinto de 1
					g++;
					System::Console::WriteLine("---------------------------------------{0}",cantrect);
				}
				else{
				classes.push_back(imgs[i].getclass());
				faces.push_back(rects[0]);
				images.push_back(imgs[i].getIimage());
				}
			}

			// ordenar por clases
			for (int i = 0; i < cantimg-1; i++)
			{
				for (int j = i+1; j < cantimg; j++)
				{
					if(classes.at(i)>classes.at(j)){


					}
				}
			}



			return nullptr;
		}
	};

	class HoldOutCrossValidation: public IExperimenter{
	public:
		HoldOutCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedImageProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {


			return nullptr;
		}
	};
}
#endif