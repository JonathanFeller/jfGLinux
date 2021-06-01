#pragma once
#include "time.h"

class Timing
{
private:
	timespec m_lastTime;
	float m_dt;
	float m_fps;

public:
	Timing();

	void Reset();

	float dt();
	float getFps();
};