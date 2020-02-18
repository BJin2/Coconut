#include "Time.h"

void Time::Start()
{
	last_tick_time = GetTickCount64();
	deltaTime = 0;
	timeSinceLastUpdate = 0;
}

void Time::Update()
{
	ULONGLONG tick_time = GetTickCount64();
	deltaTime = (tick_time - last_tick_time)/1000.0f;
	last_tick_time = tick_time;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

float Time::GetTimeSinceLastUpdate()
{
	return timeSinceLastUpdate;
}

void Time::SetTimeSinceLastUpdate(float dt)
{
	timeSinceLastUpdate += dt;
}

