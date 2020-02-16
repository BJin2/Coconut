#pragma once
#include <Windows.h>
#include <sysinfoapi.h>

class Time
{
	float last_tick_time;
	float deltaTime;
	float timeSinceLastUpdate;
public:
	void Start();
	void Update();
	float GetDeltaTime();
	float GetTimeSinceLastUpdate();
	void SetTimeSinceLastUpdate(float dt);
};