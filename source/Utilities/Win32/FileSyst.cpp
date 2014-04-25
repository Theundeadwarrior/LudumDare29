/*
 * FileSyst.cpp
 *
 * This class will look into a directory and retrieve the name of every file into it.
 * Even if there is sub-directories, the class will check them too.
 *
 *  Created on: 2010-06-11
 *  Modified on: 2012-03-08
 */

#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <ShObjIdl.h>
#include "FileSyst.h"

namespace Atum
{
namespace Win32Utilities
{

//////////////////////////////////////////////////////////////////////////////

FileSyst::FileSyst(){
	CoInitialize(NULL);
	root = OpenFolder();
	//Create vector of fileNames from directory
	TransverseDirectory(root,directories);
}
/**
 * Parameter path: the path where you want to get the files (without the '\' at the end)
 */
FileSyst::FileSyst(const std::string& userPath){
	CoInitialize(NULL);
	root = userPath;
	//Create vector of fileNames from directory
	TransverseDirectory(userPath,directories);
}

FileSyst::~FileSyst(){
	CoUninitialize();
}

void FileSyst::TransverseDirectory(std::string path, std::vector<directoryvector>& directory) {

	if ( path.empty() )
		return;
	struct _finddatai64_t data;
	std::string fname = path + "\\*.*";

	try {
		long h = _findfirsti64(fname.c_str(),&data);

		if(h >= 0) {
			directoryvector currentvector;
			directory.push_back(currentvector);

			//get iterator to the currentvector element
			unsigned int currentIndex = directory.size() -1;

			//Adds the current path to the current vector
			directory[currentIndex].path = path;

			do {
				if( (data.attrib & _A_SUBDIR) ) {
					// make sure we skip "." and "..".  Have to use strcmp here because
					// some file names can start with a dot, so just testing for the
					// first dot is not sufficient.
					if( strcmp(data.name,".") != 0 &&strcmp(data.name,"..") != 0) {
						// We found a sub-directory, so get the files in it too
						fname = path + "\\" + data.name;
						// recursion here!
						TransverseDirectory(fname, directory);
					}
				}
				else {
					// this is just a normal filename.  So just add it to our vector
					file newFile = CreateFile(data.name);
					directory[currentIndex].files.push_back(newFile);

				}
			} while( _findnexti64(h,&data) == 0);
			_findclose(h);
		}

	}  catch (std::exception& e){
		throw; }
}

std::ostream& operator<< (std::ostream& out, FileSyst& fileSyst){
	fileSyst.DisplayDirectory(out);
	return out;
}

void FileSyst::DisplayDirectory(std::ostream& out) {
	std::vector<directoryvector>::iterator i;
	std::vector<file>::iterator j;
	for (i = directories.begin(); i != directories.end(); i++){
		for (j = (*i).files.begin(); j != (*i).files.end(); j++){
			out << (*i).path + "\\";
			out << (*j).fileName << "." << (*j).extension << std::endl;
		}
	}
}

/*
 * Creates a name+extension with a file name.
 */
file FileSyst::CreateFile (std::string fileName){

	std::string fileNameCopy = fileName;
	file newFile;
	std::string name;
	std::string extension;

	//first, let's find the extension
	int numExt = fileName.find_last_of('.');
	extension = fileName.erase(0,numExt+1);

	//and let's find the name of the file (truncate the extension)
	int strLength = fileNameCopy.length();
	name = fileNameCopy.erase(numExt,strLength);

	newFile.fileName = name;
	newFile.extension = extension;

	return newFile;

}

/*
 * Returns a vector with every file in the directory
 * Param putExtension: True if you want to get the fileName+extension
 */
std::vector<std::string> FileSyst::GetAllFiles(bool putExtension){
	std::vector<std::string> result;
	std::vector<directoryvector>::iterator i;
	std::vector<file>::iterator j;

	//for every file
	for (i = directories.begin(); i != directories.end(); i++){
		for (j = (*i).files.begin(); j != (*i).files.end(); j++){
			//place the filename in the vector
			//if extension + fileName are needed
			if (putExtension)
				{ result.push_back( (*j).fileName + "." + (*j).extension ); }
			//if the fileName is needed
			else { result.push_back( (*j).fileName ); }
		}
	}

	return result;
}

/*
 * Returns a vector with every file from the directory and the right extension
 * Param extension: Don't put the '.'
 * Param putExtension: True if you want to get the fileName+extension
 */
std::vector<std::string> FileSyst::GetFilesByExtension(std::string extension, bool putExtension){
	std::vector<std::string> result;
	std::vector<directoryvector>::iterator i;
	std::vector<file>::iterator j;
	extension = StringToUpper(extension);

	//for every file
	for (i = directories.begin(); i != directories.end(); i++){
		for (j = (*i).files.begin(); j != (*i).files.end(); j++){

			//if the file has the right extension
			std::string fileExtension = StringToUpper( (*j).extension );
			if (extension == fileExtension){
				//if extension + fileName are needed
				if (putExtension)
					{ result.push_back( (*j).fileName + "." + (*j).extension ); }
				//if the fileName is needed
				else { result.push_back( (*j).fileName ); }

			}
		}
	}

	return result;
}

/* Will list all the files which have the given extension 
* extension: The extension (without the dot)
* putExtension: If the extension should be displayed
*/
std::vector<std::string> FileSyst::GetFilesPathByExtension(std::string extension, bool putExtension){
	std::vector<std::string> result;
	std::vector<directoryvector>::iterator i;
	std::vector<file>::iterator j;
	extension = StringToUpper(extension);

	//for every file
	for (i = directories.begin(); i != directories.end(); i++){
		for (j = (*i).files.begin(); j != (*i).files.end(); j++){

			//if the file has the right extension
			std::string fileExtension = StringToUpper( (*j).extension );
			if (extension == fileExtension){
				//if extension + fileName are needed
				if (putExtension) { 
					result.push_back( (*i).path + "\\" + (*j).fileName + "." + (*j).extension ); }
				//if the fileName is needed
				else { 
					result.push_back( (*i).path + "\\" + (*j).fileName ); }

			}
		}
	}

	return result;
}

std::vector<std::string> FileSyst::GetFilesByPath(std::string userPath, bool putExtension){
	std::vector<std::string> result;
	std::vector<directoryvector>::iterator i;
	std::vector<file>::iterator j;

	if (userPath < root)
		throw std::exception("Wrong path");

	//for every file
	for (i = directories.begin(); i != directories.end(); i++){
		if (!userPath.compare( (*i).path) ){
			for (j = (*i).files.begin(); j != (*i).files.end(); j++){
					//if extension + fileName are needed
					if (putExtension)
						{ result.push_back( (*j).fileName + "." + (*j).extension ); }
					//if the fileName is needed
					else { result.push_back( (*j).fileName ); }
			}
		}
	}
	return result;
}

/*
 * Returns the main path
 */
std::string FileSyst::GetRootFolder() const{
	return root;
}


////////////////////////////////////////////////////////////////////

std::string StringToUpper(std::string strToConvert){
	//change each element of the string to upper case
   for( unsigned int i=0; i<strToConvert.length(); i++) {
      strToConvert[i] = toupper(strToConvert[i]);
   }
   return strToConvert;
}

std::string StringToLower(std::string strToConvert){
	//change each element of the string to lower case
   for(unsigned int i=0;i<strToConvert.length();i++) {
      strToConvert[i] = tolower(strToConvert[i]);
   }
   return strToConvert;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

/* 
* OpenFileName
* Opens a folder dialog box, and returns the path
* Returns an empty string if dialog is canceled
*/
std::string OpenFolder(/*char *filter,*/ HWND owner) {
	HRESULT hr;
	IFileOpenDialog *pOpenFolderDialog;
	std::string folderPath;

	// CoCreate the dialog object.
	hr = CoCreateInstance(CLSID_FileOpenDialog, 
		NULL, 
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pOpenFolderDialog));

	if (SUCCEEDED(hr))
	{
		pOpenFolderDialog->SetOptions(FOS_PICKFOLDERS);

		// Show the dialog
		hr = pOpenFolderDialog->Show(owner);

		if (SUCCEEDED(hr))
		{
			// Obtain the result of the user's interaction with the dialog.
			IShellItem *psiResult;
			hr = pOpenFolderDialog->GetResult(&psiResult);

			LPWSTR folderW = NULL;
			psiResult->GetDisplayName(SIGDN_FILESYSPATH, &folderW);
			char* folderC;
			folderC = new char[300];
			folderPath = wcstombs(folderC,folderW, 300);
			folderPath = folderC;

			//free memory
			if (folderC) delete[] folderC;
			CoTaskMemFree ( folderW );
			psiResult->Release();
		}
	}
	pOpenFolderDialog->Release();
	return folderPath;
}

}
}