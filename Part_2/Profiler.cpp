#include "Profiler.h"

#include <numeric>

Profiler Profiler::m_instance;

Profiler &Profiler::getInstance()
{
	return m_instance;
}

void Profiler::addTime(long long time)
{
	m_currentFrameTotals.push_back(time);
}

void Profiler::nextFrame()
{
	// Calculate the average time of the current frame
	long long frameTotal = std::accumulate(m_currentFrameTotals.begin(), m_currentFrameTotals.end(), (long long)0);

	// Add this average to session list
	m_currentSessionTotals.push_back(frameTotal);

	// Clear the current frame totals;
	m_currentFrameTotals.clear();
}

long long Profiler::getSessionAverage()
{
	// Calculate the average time of the entire session
	return std::accumulate(m_currentSessionTotals.begin(), m_currentSessionTotals.end(), (long long)0) / (long long)m_currentSessionTotals.size();
}

void Profiler::reset()
{
	m_currentFrameTotals = {};
	m_currentSessionTotals = {};
}

Profiler::Profiler()
{
	reset();
}

Profiler::~Profiler()
{
}
