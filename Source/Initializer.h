#pragma once
#include<Windows.h>

#define MB 1048576

class Initializer
{
private:
	HWND hWnd;
public:
	bool CheckRequirements(LPCTSTR gameTitle, const DWORDLONG neededStorage, const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded);
	bool CheckMemory(const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded);
	DWORD ReadCpuSpeed();
	char* ReadCpuArchitecture();
	bool CheckStorage(const DWORDLONG diskSpaceNeeded);
	bool IsOnlyInstance(LPCTSTR gameTitle);
};

