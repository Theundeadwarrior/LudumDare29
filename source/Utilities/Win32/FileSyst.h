/*
 * FileSyst.h
 *
 * This class will look into a directory and retrieve the name of every file into it.
 * Even if there is sub-directories, it will check them too.
 *
 *  Created on: 2010-11-26
 */

#ifndef FILESYST_H_
#define FILESYST_H_

#include <iostream>
#include <vector>
#include <windows.h>

#include <tchar.h>

namespace Atum
{
namespace Win32Utilities
{

/*
 * Describes a file (name.extension)
 */
struct file{
	std::string fileName;
	std::string extension;
};

/*
 * Describes a directory.
 * Each directory contains a path, the files and the
 * sub-directories.
 */
struct directoryvector{
	std::string path;
	std::vector<file> files;
};
////////////////////////////////////////////////////////////////////////

class FileSyst{
	private:
		std::string root;
		std::vector<directoryvector> directories;

		static void TransverseDirectory(std::string, std::vector<directoryvector>&);
		static file CreateFile(std::string);
		void DisplayDirectory(std::ostream& out) ;

	public:
		FileSyst(); //will open a window to ask you the folder
		FileSyst(const std::string& path);
		~FileSyst();
		
		std::vector<std::string> GetAllFiles(bool=false);
		std::vector<std::string> GetFilesPathByExtension(std::string extension, bool putExtension=false);
		std::vector<std::string> GetFilesByExtension(std::string extension, bool putExtension=false);
		std::vector<std::string> GetFilesByPath(std::string userPath, bool putExtension=false);
		std::string GetRootFolder() const;

		friend std::ostream& operator<< (std::ostream& out, FileSyst& fileSyst);
};

////////////////////////////////////////////////////////////////////////

//Non-member functions
std::string StringToUpper(std::string);
std::string StringToLower(std::string);
std::wstring s2ws(const std::string& s);

std::string OpenFolder(/*char *filter,*/ HWND owner=NULL);

}
}

#endif /* FILESYST_H_ */
