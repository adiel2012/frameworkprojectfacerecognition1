#ifndef _coreh
#include "core.h"
#endif


#ifndef _core_experimenth
#define _core_experimenth

#include <time.h>
//using namespace System::Xml;

namespace core_experiment {
	//--------------------------------------------------------------------------------------------------
	class IExperimenter{

	protected:
		core::IFaceDetector* _detector;
		core::IFaceRecognitor* _recognitor;
		core::IClassifiedFaceProvider* _imgprovider;
	public :
		virtual float* getResults() = 0;
		virtual void  configure(System::Xml::XmlReader^ config) = 0;

		//getters
		core::IFaceDetector* getdetector(){
			return _detector;
		}

		core::IFaceRecognitor* getrecognitor(){
			return _recognitor;
		}

		core::IClassifiedFaceProvider* getimgprovider(){
			return _imgprovider;
		}
		//setters
		void setdetector(core::IFaceDetector* adetector){ _detector=adetector;  }
		void setrecognitor(core::IFaceRecognitor* arecognitor){_recognitor=arecognitor;}
		void setimgprovider(core::IClassifiedFaceProvider* aimgprovider){_imgprovider=aimgprovider;}


		IExperimenter (core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider){
			_detector = adetector;
			_recognitor = arecognitor;
			_imgprovider = aimgprovider;
		}
	};
	//--------------------------------------------------------------------------------------------------------

	class TenfoldCrossValidation: public IExperimenter{
	public:
		virtual void  configure(System::Xml::XmlReader^ config){}
		TenfoldCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {




			int g = 0;
			int cantimg = -1;
			core::ClassifiedImage* imgs = this->_imgprovider->getImages(cantimg,_detector);//  _imgprovider->getImages();
			std::vector<cv::Mat> faces;
			std::vector<int> labels;

			for (int i = 0; i < cantimg; i++)
			{
				faces.push_back((imgs[i].getIimage()));
				labels.push_back(imgs[i].getclass());
			}

			_recognitor->train(faces,labels);


			int im_width = imgs[0].getIimage().cols;
			int im_height = imgs[0].getIimage().rows;

			for (int i = 0; i < labels.size(); i++)
			{
				cv::Mat face_resized;
				cv::resize(faces[i], face_resized, cv::Size(im_width, im_height), 1.0, 1.0, cv::INTER_CUBIC);
				System::Console::WriteLine(System::Convert::ToString(labels[i])+"     "+_recognitor->recognize(&face_resized));
				//System::Console::ReadKey();
			}

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
		virtual void  configure(System::Xml::XmlReader^ config){}
		HoldOutCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {


			return nullptr;
		}
	};


	class dependencyInjector
	{
	protected:
		//dependencyInjector( ){}
		//static dependencyInjector* instance;

		core_experiment::IExperimenter* experimenter ;
	public:
		dependencyInjector(System::String^ apath ){
		//	if(instance== nullptr)
		//		instance= new dependencyInjector();

			System::Xml::XmlReader^  reader  =  System::Xml::XmlReader::Create(apath);

			reader->MoveToContent();
			System::String^ experimentername = reader->GetAttribute("type");

			System::Activator::CreateInstance(experimentername,nullptr);

			reader->ReadToFollowing("detector");
			reader->MoveToContent();

			System::Xml::XmlReader^ xmldetect = reader->ReadSubtree();
			xmldetect->MoveToContent();
			//System::Console::WriteLine(xmldetect->GetAttribute("type"));


			reader->ReadToFollowing("recognitor");
			reader->MoveToContent();
			System::Xml::XmlReader^ xmlrecognitor = reader->ReadSubtree();
			xmlrecognitor->MoveToContent();
			//System::Console::WriteLine(xmlrecognitor->GetAttribute("type"));

			reader->ReadToFollowing("faceprovider");
			reader->MoveToContent();
			System::Xml::XmlReader^ xmlfaceprovider = reader->ReadSubtree();
			xmlfaceprovider->MoveToContent();
			//System::Console::WriteLine(xmlfaceprovider->GetAttribute("type"));



			core::IFaceDetector* detector ;
			core::IFaceRecognitor* reconocedor ;
			core::IClassifiedFaceProvider* classifiedFaceProvider ;
			core_experiment::IExperimenter* experimeto ;

			//FALTA CREAR   LAS INSTANCIAS

			detector->configure(xmldetect);
			reconocedor->configure(xmlrecognitor);
			classifiedFaceProvider->configure(xmlfaceprovider);
			experimeto->configure(reader);

			experimeto->setdetector(detector);
			experimeto->setimgprovider(classifiedFaceProvider);
			experimeto->setrecognitor(reconocedor);

			

			experimenter = experimeto;

			//return nullptr;

		}
		~dependencyInjector( ){}

		core_experiment::IExperimenter* getExperimenter(){
			return experimenter;
		}
	};

	class XmlRunner{
	private:
		void saveResults(float* results,core_experiment::IExperimenter* experimentador){
			
		}

	public:

		XmlRunner(){}
		void run(System::String^  path){

			dependencyInjector* injector = new dependencyInjector(path);


			float* results = injector->getExperimenter()->getResults();
			saveResults(results,injector->getExperimenter());


			delete [] results;

		}
		//ejecuta todos
		void run(){

			//using namespace System;
			//using namespace System::IO;
			System::String^ folder =   System::IO::Directory::GetCurrentDirectory()+"\\experiments";  // "C:\\";
			array<System::String^>^ dir = System::IO::Directory::GetFiles( folder );
			//Console::WriteLine("--== Directories inside '{0}' ==--", folder);
			int aclass = -1;
			for (int i=0; i<dir->Length; i++){
				System::String^ file =   dir[i];
				System::Console::WriteLine(file);
				//run( (char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(file));
				run(file);
			}


		}


	};


}
/*
class dependencyInjector{
private:
//static char* path;
static dependencyInjector* _instance  ;
//core_experiment::IExperimenter* experimenter;

dependencyInjector(){

} 

public:

static dependencyInjector* getInstance(System::String^ apath){
//path=apath;

XmlReader^  reader  =  XmlReader::Create(apath);

reader->MoveToContent();
System::String^ experimentername = reader->GetAttribute("type");

System::Activator::CreateInstance(experimentername,nullptr);

reader->ReadToFollowing("detector");
reader->MoveToContent();

XmlReader^ xmldetect = reader->ReadSubtree();
xmldetect->MoveToContent();
//System::Console::WriteLine(xmldetect->GetAttribute("type"));


reader->ReadToFollowing("recognitor");
reader->MoveToContent();
XmlReader^ xmlrecognitor = reader->ReadSubtree();
xmlrecognitor->MoveToContent();
//System::Console::WriteLine(xmlrecognitor->GetAttribute("type"));

reader->ReadToFollowing("faceprovider");
reader->MoveToContent();
XmlReader^ xmlfaceprovider = reader->ReadSubtree();
xmlfaceprovider->MoveToContent();
//System::Console::WriteLine(xmlfaceprovider->GetAttribute("type"));



core::IFaceDetector* detector ;
core::IFaceRecognitor* reconocedor ;
core::IClassifiedFaceProvider* classifiedFaceProvider ;
core_experiment::IExperimenter* experimeto ;

//FALTA CREAR   LAS INSTANCIAS

detector->configure(xmldetect);
reconocedor->configure(xmlrecognitor);
classifiedFaceProvider->configure(xmlfaceprovider);
experimeto->configure(reader);

experimeto->setdetector(detector);
experimeto->setimgprovider(classifiedFaceProvider);
experimeto->setrecognitor(reconocedor);

//	experimenter=experimeto;
//core_experiment::dependencyInjector::instance = new core_experiment::dependencyInjector();
//core_experiment::dependencyInjector::instance.experimenter = experimeto;

//core_experiment::dependencyInjector::_instance = new core_experiment::dependencyInjector();
return dependencyInjector::_instance;


}	

};

class XmlRunner{
private:
void saveResults(float* results,core_experiment::IExperimenter* experimentador){

}

public:

XmlRunner(){}
void run(System::String^  path){

dependencyInjector* injector = dependencyInjector::getInstance(path);


//float* results = injector->getExperimenter()->getResults();
//saveResults(results,injector->getExperimenter());


//delete [] results;

}
//ejecuta todos
void run(){

using namespace System;
using namespace System::IO;
System::String^ folder =   System::IO::Directory::GetCurrentDirectory()+"\\experiments";  // "C:\\";
array<System::String^>^ dir = System::IO::Directory::GetFiles( folder );
//Console::WriteLine("--== Directories inside '{0}' ==--", folder);
int aclass = -1;
for (int i=0; i<dir->Length; i++){
System::String^ file =   dir[i];
Console::WriteLine(file);
//run( (char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(file));
run(file);
}


}


};
*/

#endif