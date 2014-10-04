#ifndef _coreh
#include "core.h"
//#include "core_config.h"
#endif


#ifndef _core_experimenth
#define _core_experimenth


#include <time.h>
//using namespace System::Xml;


//   incluir los .h

#include "allcore.h"
#include "MiDetector.h"
#include "MiDetector2.h"
#include "MiReconocedorFacial.h"
#include "AttImgProvider.h"



namespace core_experiment {
	//--------------------------------------------------------------------------------------------------
	class IExperimenter{

	protected:
		core::IFaceDetector* _detector;
		core::IFaceRecognitor* _recognitor;
		core::IClassifiedFaceProvider* _imgprovider;
	public :
		virtual float* getResults(int& cant,float*& trainingresults) = 0;
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
		IExperimenter(){}
	};
	//--------------------------------------------------------------------------------------------------------

	class TenfoldCrossValidation: public IExperimenter{
	public:
		TenfoldCrossValidation():IExperimenter(){}
		virtual void  configure(System::Xml::XmlReader^ config){}
		TenfoldCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults(int& cant,float*& trainingresults) {


			cant=10;

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
		virtual float* getResults(int& cant,float*& trainingresults) {


			return nullptr;
		}

		HoldOutCrossValidation(){}
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


			//System::Object^ itemexperimentername = System::Activator::CreateInstance(System::Type::GetType(experimentername));

			reader->ReadToFollowing("detector");
			reader->MoveToContent();
			System::Xml::XmlReader^ xmldetect = reader->ReadSubtree();
			xmldetect->MoveToContent();
			//System::Console::WriteLine(xmldetect->GetAttribute("type"));
			//System::Object^ itemxmldetect = System::Activator::CreateInstance(System::Type::GetType(xmldetect->GetAttribute("type") ));

			reader->ReadToFollowing("recognitor");
			reader->MoveToContent();
			System::Xml::XmlReader^ xmlrecognitor = reader->ReadSubtree();
			xmlrecognitor->MoveToContent();
			//System::Console::WriteLine(xmlrecognitor->GetAttribute("type"));
			//System::Object^ itemxmlrecognitor = System::Activator::CreateInstance(System::Type::GetType(xmlrecognitor->GetAttribute("type")));

			reader->ReadToFollowing("faceprovider");
			reader->MoveToContent();
			System::Xml::XmlReader^ xmlfaceprovider = reader->ReadSubtree();
			xmlfaceprovider->MoveToContent();
			//System::Console::WriteLine(xmlfaceprovider->GetAttribute("type"));
			//System::Object^ itemxmlfaceprovider = System::Activator::CreateInstance(System::Type::GetType(xmlfaceprovider->GetAttribute("type")));





			/*	System::Runtime::InteropServices::GCHandle handle = System::Runtime::InteropServices::GCHandle::Alloc(itemxmlrecognitor);
			System::IntPtr pointer = System::Runtime::InteropServices::GCHandle::ToIntPtr(handle);			
			core::IFaceRecognitor* reconocedor = (core::IFaceRecognitor*)(pointer.ToPointer());            

			handle = System::Runtime::InteropServices::GCHandle::Alloc(itemxmlfaceprovider);
			pointer = System::Runtime::InteropServices::GCHandle::ToIntPtr(handle);			
			core::IClassifiedFaceProvider* classifiedFaceProvider = (core::IClassifiedFaceProvider*)(pointer.ToPointer());

			handle = System::Runtime::InteropServices::GCHandle::Alloc(itemxmldetect);
			pointer = System::Runtime::InteropServices::GCHandle::ToIntPtr(handle);			
			core::IFaceDetector* detector = (core::IFaceDetector*)(pointer.ToPointer());

			handle = System::Runtime::InteropServices::GCHandle::Alloc(itemexperimentername);
			pointer = System::Runtime::InteropServices::GCHandle::ToIntPtr(handle);			
			core_experiment::IExperimenter* experimeto = (core_experiment::IExperimenter*)(pointer.ToPointer());*/

			using namespace System::Runtime::InteropServices;

			//	char* str2 =   (char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(xmldetect->GetAttribute("type"))  ;

			core::IFaceDetector* detector = (core::IFaceDetector*) instanceprovider((char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(xmldetect->GetAttribute("type")));
			core::IFaceRecognitor* reconocedor  = (core::IFaceRecognitor*) instanceprovider((char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(xmlrecognitor->GetAttribute("type")));
			core::IClassifiedFaceProvider* classifiedFaceProvider  = (core::IClassifiedFaceProvider*) instanceprovider((char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(xmlfaceprovider->GetAttribute("type")));
			core_experiment::IExperimenter* experimeto  = (core_experiment::IExperimenter*) instanceprovider((char*)(void*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(experimentername));




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


		void* instanceprovider(char* tipo){
			void* result = nullptr;
			if(strcmp(tipo,"core_experiment.TenfoldCrossValidation")==0){
				result = new TenfoldCrossValidation();
			}
			else if(strcmp(tipo,"core_experiment.HoldOutCrossValidation")==0){
				result = new HoldOutCrossValidation();
			}


			// put the detectors
			else if(strcmp(tipo,"added_namespace.MiDetector2")==0){
				result = new added_namespace::MiDetector2(); 
			}



			// put the rocognizers
			else if(strcmp(tipo,"added_namespace.MiReconocedorFacial")==0){
				result = new added_namespace:: MiReconocedorFacial(); 
			}





			//put the provider
			else if(strcmp(tipo,"providers.AttImgProvider")==0){
				result = new providers:: AttImgProvider(); 
			}

			//if(typeid(result)==typeid(core::IConfigurable*))

			return result;
		}



		~dependencyInjector( ){}

		core_experiment::IExperimenter* getExperimenter(){
			return experimenter;
		}


	};

	class XmlRunner{
	private:
		void saveResults(float* results,int cant,core_experiment::IExperimenter* experimentador,System::String^  path,float* trainingresults){

			time_t t = time(NULL);
			tm s;
			gmtime_s(&s, &t);
			//printf("UTC Time:   %02i:%02i:%02i\n",s.tm_hour, s.tm_min, s.tm_sec);
			localtime_s(&s, &t);
			//printf("Local Time: %02i:%02i:%02i\n",s.tm_hour, s.tm_min, s.tm_sec);

			System::String^ folder =   System::IO::Directory::GetCurrentDirectory()+"\\experimentsresults\\";

			System::IO::FileInfo finfo(path);
			System::String^  aname = finfo.Name;



			System::String^ moment= "_"+s.tm_year+"_"+(s.tm_mon+1)+"_"+s.tm_mday+"_"+   s.tm_hour+"_"+s.tm_min+"_"+s.tm_sec;
			System::Console::WriteLine(System::IO::Directory::GetCurrentDirectory()+"\\experimentsresults\\"+aname->Substring(0,aname->LastIndexOf("."))+moment+".txt") ;

			System::IO::FileInfo finforesult(System::IO::Directory::GetCurrentDirectory()+"\\experimentsresults\\"+aname->Substring(0,aname->LastIndexOf("."))+moment+".txt");
			//finforesult.Create();

			System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(finforesult.FullName);
			double sumageneralization=0;
			double sumatrainning=0;
			for (int i = 0; i < cant; i++)
			{
				sw->WriteLine("{0},{1}",results[i],trainingresults[i]);
				sumatrainning += trainingresults[i];
				sumageneralization +=results[i];
			}
			sw->WriteLine("{0},{1}",sumatrainning/cant,sumageneralization/cant);
			sw->Close();



		}

	public:

		XmlRunner(){}
		void run(System::String^  path){

			dependencyInjector* injector =  new dependencyInjector(path);     //nullptr; // 

			int cant=6;

			float* trainingresults = new float[cant];
			float* generalizationresults =   new float[cant];                // injector->getExperimenter()->getResults(cant,trainingresults);

			saveResults(generalizationresults,cant,nullptr,path,trainingresults);
			//saveResults(results,cant,injector->getExperimenter(),path);


			delete [] trainingresults;
			delete [] generalizationresults;

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