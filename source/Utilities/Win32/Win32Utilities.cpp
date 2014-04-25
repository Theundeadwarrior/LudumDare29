#include "Win32Utilities.h"
#include <windows.h>
#include <ShObjIdl.h>
#include <Shlobj.h>

namespace Atum
{
	namespace Win32Utilities
	{

		std::string OpenFileDialog( const std::vector<std::string>& extensionList)
		{
			CoInitialize(NULL);

			HRESULT hr;
			IFileOpenDialog *pOpenFileDialog;
			std::string filePath;

			// CoCreate the dialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, 
				NULL, 
				CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(&pOpenFileDialog));

			if (SUCCEEDED(hr))
			{
				COMDLG_FILTERSPEC* saveTypes = new COMDLG_FILTERSPEC[extensionList.size()];
				for ( int i = 0; i < extensionList.size(); i++)
				{
					WCHAR* extension = new WCHAR[extensionList[i].size()+1];
					MultiByteToWideChar(0,0, extensionList[i].c_str(), -1, extension, extensionList[i].size()+1);

					saveTypes[i].pszName = extension;
					saveTypes[i].pszSpec = extension;
				}
				hr = pOpenFileDialog->SetFileTypes(extensionList.size(), saveTypes);

				if (SUCCEEDED(hr)) 
				{
					// Show the dialog
					hr = pOpenFileDialog->Show(GetActiveWindow());

					if (SUCCEEDED(hr))
					{
						// Obtain the result of the user's interaction with the dialog.
						IShellItem *psiResult;
						hr = pOpenFileDialog->GetResult(&psiResult);

						LPWSTR folderW = NULL;
						psiResult->GetDisplayName(SIGDN_FILESYSPATH, &folderW);
						char* folderC;
						folderC = new char[300];
						filePath = wcstombs(folderC,folderW, 300);
						filePath = folderC;

						//free memory
						if (folderC) delete[] folderC;
						CoTaskMemFree ( folderW );
						psiResult->Release();
					}
				}
				for ( int i = 0; i < extensionList.size(); i++)
				{
					delete[] saveTypes->pszSpec;
				}
				delete[] saveTypes;
			}

			CoUninitialize();

			pOpenFileDialog->Release();
			return filePath;
		}

		bool CreateFolder( const std::string& folderPath )
		{
			return SHCreateDirectoryEx(0, folderPath.c_str(), 0) == ERROR_SUCCESS;
		}

	}
}
