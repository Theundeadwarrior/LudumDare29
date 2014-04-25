#include "Debug.h"

#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <Windows.h>
#include <iostream>

namespace Atum
{
	namespace Utilities
	{
		void OutputTrace(char* text, ...)
		{
			char buffer[256];
			va_list args;
			va_start (args, text);
			vsprintf_s (buffer, text, args);
			OutputDebugString (buffer);
			va_end (args);
		}

		void OutputError(char* text, ...)
		{
			char buffer[256];
			va_list args;
			va_start (args, text);
			vsprintf_s (buffer,text, args);
			perror (buffer);
			// Make crash?
			va_end (args);
		}

		void OutputAssert( const char* _condition, const char* _message, char* _filename, char* _line )
		{
			std::string condition(_condition);
			std::string message(_message);
			std::string file(_filename);
			std::string line(_line);

			// Remove the path if there is a path
			int fileNameBeginPosition = file.find_last_of("\\");
			if(fileNameBeginPosition != file.size())
			{
				file.erase(0,fileNameBeginPosition + 1);
				file.erase(file.size() - 1, 1);
			}

			std::string errorMessage("[ASSERT] Condition: ");
			errorMessage.append(condition);
			errorMessage.append(" failed. ");
			errorMessage.append("Error in file ");
			errorMessage.append(file);
			errorMessage.append(" at line ");
			errorMessage.append(line);
			errorMessage.append(". ");
			errorMessage.append(message);
			OutputDebugString(errorMessage.c_str());
			perror(errorMessage.c_str());

			// make crash?
		}

	}
}
