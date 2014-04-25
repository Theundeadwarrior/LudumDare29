#include "Timer.h"

namespace Atum
{
namespace Utilities
{

Timer* Timer::instance = NULL;

Timer::Timer()
{
	ResetTimer();
}

void Timer::ResetTimer()
{
	mo_ReferenceTime = clock();
	mo_LapTime = clock();
}

void Timer::MarkLap()
{
	mo_LapTime = clock();
	timeLap = ( mo_LapTime - mo_ReferenceTime ) / float(CLOCKS_PER_SEC);
}

float Timer::GetTime() const
{
	return (clock() - mo_ReferenceTime) / float(CLOCKS_PER_SEC);
}

}
}