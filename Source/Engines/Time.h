#pragma once
#include <Windows.h>
#include <sysinfoapi.h>

class Time
{
	float last_tick_time;
	float deltaTime;

public:
	void Start();
	void Update();
	float GetDeltaTime();
};