#pragma once
#include<iostream>
#include<Windows.h>
#include<direct.h>

#define MB 1048576

class Initializer
{
public:
	Initializer();

	bool CheckMemory(const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded);
	DWORD ReadCpuSpeed();
	char* ReadCpuArchitecture();
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool IsOnlyInstance(LPCTSTR gameTitle);
};

