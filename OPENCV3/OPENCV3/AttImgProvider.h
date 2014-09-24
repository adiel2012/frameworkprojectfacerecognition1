#include "core.h"
#include "core2.h"
#include "core_experiment.h"
#include "opencv_core.h"

//#include <iostream>
using namespace System;
using namespace System::Runtime::InteropServices;

namespace providers
{
	class AttImgProvider : public core::IClassifiedFaceProvider {

	public:
		AttImgProvider():core::IClassifiedFaceProvider(){
			int g = 0;
		}



		virtual core::ClassifiedImage* getImages(int& numimages, core::IFaceDetector* adetector){
			//char* path = "";
			
			int pos = 0;

			std::vector<int> classes;
			//std::vector<core::Rectangle> faces;
			std::vector<Mat> images;

			using namespace System;
			using namespace System::IO;
			System::String^ folder =   System::IO::Directory::GetCurrentDirectory()+"\\datasets\\att_faces";  // "C:\\";
			array<System::String^>^ dir = System::IO::Directory::GetDirectories( folder );
			//Console::WriteLine("--== Directories inside '{0}' ==--", folder);
			int aclass = -1;
			for (int i=0; i<dir->Length; i++){
				System::String^ subfolder =   dir[i];
				//Console::WriteLine(subfolder);
				System::String^ temp = (System::String^)subfolder->Clone();
				System::String^temp2 = temp->Substring(temp->LastIndexOf("\\")+2);
				System::Console::WriteLine(temp2+"     "+temp   );
				aclass = Convert::ToInt32(temp2)-1;

				array<System::String^>^ file = System::IO::Directory::GetFiles( subfolder );
				//Console::WriteLine("--== Files inside '{0}' ==--", subfolder);
				for (int i=0; i<file->Length; i++){
					//Console::WriteLine("       "+file[i]);



					//  deteccion
					//for (int i = 0; i < cantimg; i++)
					//{

						IplImage* imagen = cvLoadImage((char*)Marshal::StringToHGlobalAnsi(file[i]).ToPointer());
						int cantrect = -1;
						
				        std::vector<cv::Rect> rectangles;
						Mat* rects = adetector->detect(imagen,cantrect,rectangles);
						//System::Console::WriteLine(i);

						if(cantrect!=1)
						{
							// ver que se hace sui la cantidad de caras es distinto de 1
							//g++;
						//	System::Console::WriteLine("---------------------------------------{0}",i);
						}
						else{
							classes.push_back(aclass);
							//faces.push_back(rects[0]);
							images.push_back(rects[0]);
						}
					//}


					/*result[pos].setclass(aclass);
					result[pos].setIimage();
					pos++;*/

				}
			}

			/*array<String^>^ file = Directory::GetFiles( folder );
			Console::WriteLine("--== Files inside '{0}' ==--", folder);
			for (int i=0; i<file->Length; i++)
			Console::WriteLine(file[i]);*/

			//int cant = 400;
			core::ClassifiedImage* result = new core::ClassifiedImage[classes.size()];
			for (int i = 0; i < classes.size(); i++)
			{
				result[i].setclass(classes[i]);
				result[i].setIimage(images[i]);
			}

			numimages= classes.size();
			Console::WriteLine(pos);
			return result;

		}

	};


}