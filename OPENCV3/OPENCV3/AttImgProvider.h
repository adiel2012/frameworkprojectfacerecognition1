#include "core.h"
#include "core2.h"
#include "core_experiment.h"
#include "opencv_core.h"

//#include <iostream>
//using namespace System;
using namespace System::Runtime::InteropServices;

namespace providers
{
	class AttImgProvider : public core::IClassifiedImageProvider {

	public:
		AttImgProvider():core::IClassifiedImageProvider(){
			int g = 0;
		}



		virtual core::ClassifiedImage* getImages(int& numimages){
			//char* path = "";
			int cant = 400;
			core::ClassifiedImage* result = new core::ClassifiedImage[cant];
			int pos = 0;

			using namespace System;
			using namespace System::IO;
			String^ folder =   Directory::GetCurrentDirectory()+"\\datasets\\att_faces";  // "C:\\";
			array<String^>^ dir = Directory::GetDirectories( folder );
			//Console::WriteLine("--== Directories inside '{0}' ==--", folder);
			int aclass = -1;
			for (int i=0; i<dir->Length; i++){
				String^ subfolder =   dir[i];
				//Console::WriteLine(subfolder);
				String^ temp = (String^)subfolder->Clone();
				String^temp2 = temp->Substring(temp->LastIndexOf("\\")+2);
				Console::WriteLine(temp2);
				aclass = Convert::ToInt32(temp2)-1;

				array<String^>^ file = Directory::GetFiles( subfolder );
				//Console::WriteLine("--== Files inside '{0}' ==--", subfolder);
				for (int i=0; i<file->Length; i++){
					//Console::WriteLine("       "+file[i]);
					result[pos].setclass(aclass);
					result[pos].setIimage( cvLoadImage((char*)Marshal::StringToHGlobalAnsi(file[i]).ToPointer()));
					pos++;
					
				}
			}

			/*array<String^>^ file = Directory::GetFiles( folder );
			Console::WriteLine("--== Files inside '{0}' ==--", folder);
			for (int i=0; i<file->Length; i++)
			Console::WriteLine(file[i]);*/

			numimages= pos;
			Console::WriteLine(pos);
			return result;

		}

	};


}