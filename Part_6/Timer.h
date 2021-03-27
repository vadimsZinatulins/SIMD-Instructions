#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();
private:
	using TimePoint = std::chrono::steady_clock::time_point;

	TimePoint m_startTime;
};

#endif // !__TIMER_H__
