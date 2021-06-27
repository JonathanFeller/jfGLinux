#include "jfGL.h"
#include "Timing.h"

Timing::Timing()
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_lastTime);
	m_dt = 0.1f;
	m_fps = 1.0f;
}

float Timing::getFps()
{
	return m_fps;
}

float Timing::dt()
{
	return m_dt;
}

void Timing::Reset()
{
	timespec currentTime = {0};
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);
	float delta = (float)((currentTime.tv_sec - m_lastTime.tv_sec) * 1000000000 + (currentTime.tv_nsec - m_lastTime.tv_nsec)) / 1000000000.0f;
	m_dt = delta > 1.0f ? 1.0f : delta;
	m_fps = 1.0f / m_dt;
	m_lastTime = currentTime;
}