#ifndef UTILITIES_DEBUG_H
#define UTILITIES_DEBUG_H

// Helpers to get __FILE__ and __LINE__ to a string
#define DEBUGSTRINGIFY(x) #x
#define DEBUGTOSTRING(x) DEBUGSTRINGIFY(x)

#define ATUM_ASSERT(condition) \
	ATUM_ASSERT_MESSAGE(condition,"")

#define ATUM_ASSERT_MESSAGE(condition, message) \
	if(!(condition)) \
	Atum::Utilities::OutputAssert(DEBUGTOSTRING(condition), message, DEBUGTOSTRING(__FILE__), DEBUGTOSTRING(__LINE__))

#define ATUM_TRACE(input,...) Atum::Utilities::OutputTrace(input,__VA_ARGS__)
#define ATUM_ERROR(input,...) Atum::Utilities::OutputError(input,__VA_ARGS__)

namespace Atum
{
	namespace Utilities
	{
		void OutputTrace(char* text, ...);
		void OutputError(char* text, ...);
		void OutputAssert(const char* _condition, const char* _message, char* _filename, char* _line);
	}
}

#endif
