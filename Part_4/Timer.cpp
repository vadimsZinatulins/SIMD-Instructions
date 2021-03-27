#include "Timer.h"
#include "Profiler.h"

Timer::Timer() :
	m_startTime(std::chrono::high_resolution_clock::now())
{
}

Timer::~Timer()
{
	TimePoint endTime = std::chrono::high_resolution_clock::now();

	Profiler::getInstance().addTime(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime).count());
}
