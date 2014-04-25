#include "UiUtilities.h"
#include <sstream>

#include "Utilities/Win32/Win32Utilities.h"

namespace Atum
{
namespace UserInterface
{

int UiUtilities::strToInt(const std::string& toConvert)
{
	return atoi(toConvert.c_str());
}

std::string UiUtilities::intToStr( int toConvert )
{
	std::stringstream ss;
	ss << toConvert;
	return ss.str();
}

float UiUtilities::strToFloat( const std::string toConvert )
{
	return (float)atof(toConvert.c_str());
}

std::string UiUtilities::floatToStr( float toConvert )
{
	std::stringstream ss;
	ss << toConvert;
	return ss.str();
}

double UiUtilities::strToDouble( const std::string toConvert )
{
	return atof(toConvert.c_str());
}

std::string UiUtilities::doubleToStr( double toConvert )
{
	std::stringstream ss;
	ss << toConvert;
	return ss.str();
}

std::string UiUtilities::DisplayOpenFileDialog( const std::vector<std::string>& extensionList )
{
	return Win32Utilities::OpenFileDialog(extensionList);
}

std::string UiUtilities::GetFileFromPath( const std::string& fullPath )
{
	size_t found (fullPath.find_last_of("/\\") );
	if ( found != std::string::npos )
	{
		return fullPath.substr(found+1);
	}
	else
	{
		return "";
	}
}

}
}