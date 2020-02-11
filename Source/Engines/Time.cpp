#include "Time.h"

void Time::Start()
{
	last_tick_time = 0;
	deltaTime = 0;
}

void Time::Update()
{
	float tick_time = GetTickCount64();
	deltaTime = tick_time - last_tick_time;
	last_tick_time = tick_time;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

