#ifndef UTILITIES_IDGENERATOR_H
#define UTILITIES_IDGENERATOR_H

namespace Atum
{
namespace Utilities
{
	class IdGenerator
	{
	public:
		static IdGenerator& GetInstance();
		long unsigned int GenerateId();

	private:
		IdGenerator();
		IdGenerator(IdGenerator const&);
		void operator=(IdGenerator const&);
	};

}
}

#endif
