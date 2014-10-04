
#include <stdio.h>
#include <string.h>

#include "allcore.h"
#include "MiDetector.h"
#include "MiDetector2.h"
#include "MiReconocedorFacial.h"
#include "AttImgProvider.h"

void* instanceprovider(char* tipo){
	void* result = nullptr;
	if(strcmp(tipo,"core_experiment.TenfoldCrossValidation")==0){
		return new core_experiment:: TenfoldCrossValidation();
	}

	return result;
}