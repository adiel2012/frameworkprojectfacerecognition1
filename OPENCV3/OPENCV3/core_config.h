

#include "config.h"
#include <time.h>
//using namespace System::Xml;

namespace core_experiment {
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
		result = new MiDetector2(); 
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

}

