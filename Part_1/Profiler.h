#ifndef __PROFILER_H__
#define __PROFILER_H__

#include <vector>

class Profiler
{
public:
	static Profiler &getInstance();

	void addTime(long long time);
	void nextFrame();

	long long getSessionAverage();

	void reset();
private:
	Profiler();
	~Profiler();

	static Profiler m_instance;

	std::vector<long long> m_currentFrameTotals;
	std::vector<long long> m_currentSessionTotals;
};

#endif // !__PROFILER_H__
