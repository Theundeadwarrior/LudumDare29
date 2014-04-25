#ifndef WIN32_UTILITIES
#define WIN32_UTILITIES

#include <string>
#include <vector>

namespace Atum
{
	namespace Win32Utilities
	{

		std::string OpenFileDialog( const std::vector<std::string>& extensionList);

		bool CreateFolder( const std::string& folderPath );

	}
}

#endif