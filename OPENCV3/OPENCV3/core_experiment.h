#ifndef _coreh
#include "core.h"
#endif


#ifndef _core_experimenth
#define _core_experimenth

using namespace System::Xml;

namespace core_experiment {
	//--------------------------------------------------------------------------------------------------
	class IExperimenter{

	protected:
		core::IFaceDetector* _detector;
		core::IFaceRecognitor* _recognitor;
		core::IClassifiedFaceProvider* _imgprovider;
	public :
		virtual float* getResults() = 0;

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
		HoldOutCrossValidation(core::IFaceDetector* adetector,  core::IFaceRecognitor* arecognitor,core::IClassifiedFaceProvider* aimgprovider):IExperimenter(adetector,arecognitor,aimgprovider){}
		virtual float* getResults() {


			return nullptr;
		}
	};
}

class dependencyInjector{
private:
	static char* path;
	static dependencyInjector* instance;
	static core_experiment::IExperimenter* experimenter;
	dependencyInjector(){

	} 

	/*static core::IFaceDetector* getDetector(System::Xml::XmlTextReader reader){

		return nullptr;
	}

	static core::IFaceRecognitor* getFaceRecognitor(System::Xml::XmlTextReader reader){

		return nullptr;
	}

	static core::IClassifiedFaceProvider* getClassifiedFaceProvider(System::Xml::XmlTextReader reader){

		return nullptr;
	}*/

	static core_experiment::IExperimenter* getExperimenter(System::Xml::XmlTextReader reader){		

		return nullptr;
	}


public:


	static dependencyInjector* getInstance(char* apath){
		path=apath;

		System::Xml::XmlTextReader reader ("");

			/*	while (reader.Read())
		{
			switch (reader.NodeType)
			{
			case XmlNodeType::Element: // The node is an element.
				Console::Write("<{0}", reader.Name);
				Console::WriteLine(">");
				break;
			case XmlNodeType::Text: //Display the text in each element.
				Console::WriteLine (reader.Value);
				break;
			case XmlNodeType::EndElement: //Display the end of the element.
				Console::Write("</{0}", reader.Name);
				Console::WriteLine(">");
				break;
			}
		}*/

		core::IFaceDetector* detector ;
		core::IFaceRecognitor* reconocedor ;
		core::IClassifiedFaceProvider* classifiedFaceProvider ;
		experimenter ;


	}
	static core_experiment::IExperimenter* getExperimenter(){		

		return nullptr;
	}



};

class XmlRunner{
private:
	void saveResults(float* results,core_experiment::IExperimenter* experimentador){

	}

public:
	void run(char* path){

		dependencyInjector* injector = dependencyInjector::getInstance(path);






		



		float* results = injector->getExperimenter()->getResults();
		saveResults(results,injector->getExperimenter());


		delete [] results;

	}
};

#endif