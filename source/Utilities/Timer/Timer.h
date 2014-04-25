#ifndef UTILITIES_TIMER_H_
#define UTILITIES_TIMER_H_

#include <ctime>

namespace Atum
{
namespace Utilities
{

class Timer
{
public:
	float timeLap;

	static Timer* GetInstance();
	
	//Resets the timer's reference time & lap time.
	void	ResetTimer();

	// Stops the timer at a certain time. (Calling this method more than once 
	// without resetting the timer sets the lap time at the last time this
	// method was called. )
	void	MarkLap();

	//Returns the time elapsed (in seconds) between the reset and the current time.
	float	GetTime() const;

	//Returns the time elapsed (in seconds) between the last reset time and the last lap time.
	float	GetLapTime() const{return timeLap;}

protected:

	clock_t mo_ReferenceTime;
	clock_t mo_LapTime;

private:
	Timer();
	static Timer* instance;
};

inline Timer* Timer::GetInstance()
{
	if(!instance)
	{
		instance = new Timer;
	}
	return instance;
}

}
}

#endif //TIMER_H_