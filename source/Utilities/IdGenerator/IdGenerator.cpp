#include "IdGenerator.h"
#include <time.h>
#include "GLM/include/glm/gtx/random.hpp"

namespace Atum
{
namespace Utilities
{
	//-----------------------------------------------------------------------------
	IdGenerator::IdGenerator()
	{
		srand (time(NULL));
	}

	//-----------------------------------------------------------------------------
	IdGenerator& IdGenerator::GetInstance()
	{
		static IdGenerator instance;
		return instance;
	}

	//-----------------------------------------------------------------------------
	long unsigned int IdGenerator::GenerateId()
	{
		return glm::compRand1(0UL,ULONG_MAX);	
	}

}
}
