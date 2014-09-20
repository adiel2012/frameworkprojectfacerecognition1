#include "core.h"
#include "core2.h"
#include "core_experiment.h"
#include "opencv_core.h"

namespace providers
{
class AttImgProvider : public core::IClassifiedImageProvider {

	public:
		AttImgProvider():core::IClassifiedImageProvider(){
			int g = 0;
		}

		

		virtual core::ClassifiedImage* getImages(){
		//char* path = "";

		using namespace System;
		using namespace System::IO;
		String^ folder = "C:\\";
		array<String^>^ dir = Directory::GetDirectories( folder );
		Console::WriteLine("--== Directories inside '{0}' ==--", folder);
		for (int i=0; i<dir->Length; i++)
		Console::WriteLine(dir[i]);

		array<String^>^ file = Directory::GetFiles( folder );
		Console::WriteLine("--== Files inside '{0}' ==--", folder);
		for (int i=0; i<file->Length; i++)
		Console::WriteLine(file[i]);

		return nullptr;

		}
		
	};


}