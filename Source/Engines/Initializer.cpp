#include<iostream>
#include<direct.h>
#include "Initializer.h"

bool Initializer::CheckRequirements(LPCTSTR gameTitle, const DWORDLONG neededStorage, const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded)
{
	hWnd = FindWindow(gameTitle, NULL);
	if (IsOnlyInstance(gameTitle))
	{
		if (CheckStorage(neededStorage * MB))
		{
			if (CheckMemory(physicalNeeded * MB, virtualNeeded * MB))
			{
				ReadCpuSpeed();
				ReadCpuArchitecture();
				return true;
			}
		}
	}
	return false;
}

bool Initializer::CheckMemory(const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);


	//Printing memory info
	printf("Total Physical Memory : %I64d MB\n", status.ullTotalPhys / MB);
	printf("Available Physical Memory : %I64d MB\n", status.ullAvailPhys / MB);
	printf("Total Virtual Memory : %I64d MB\n", status.ullTotalVirtual / MB);
	printf("Available Virtual Memory : %I64d MB\n", status.ullAvailVirtual / MB);

	//Check physical memory
	if (status.ullAvailPhys < physicalNeeded)
	{
		MessageBox(hWnd, "CheckMomory Failure : Not enough physical memory.", NULL, MB_OK);
		return false;
	}

	//Check virtual memory
	if (status.ullAvailVirtual < virtualNeeded)
	{
		MessageBox(hWnd, "CheckMomory Failure : Not enough virtual memory.", NULL, MB_OK);
		return false;
	}

	//Check if there is contiguos memory 
	char* buff = new char[virtualNeeded];
	if (buff)
	{
		delete[] buff;
	}
	else
	{
		MessageBox(hWnd, "CheckMemory Failure: Not enough contiguous memory.", NULL, MB_OK);
		return false;
	}

	return true;
}

DWORD Initializer::ReadCpuSpeed()
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)& dwMHz, &BufSize);
	}
	printf("CPU speed : %d\n", dwMHz);
	return dwMHz;
}

char* Initializer::ReadCpuArchitecture()
{
	char regVal[1024];
	//char *regVal = (char*)malloc(1024 * sizeof(char)); //If I use this one, sizeof(regVal) fixed at 8.
	//memset(regVal, NULL, 1025);
	HKEY hKey;
	DWORD size = sizeof(regVal);
	DWORD type = REG_SZ;
		
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{

		RegQueryValueEx(hKey, "ProcessorNameString", NULL, &type, (PBYTE)& regVal, &size);
		printf("CPU architecture : %s\n", regVal);
		return regVal;
	}
	else
	{
		MessageBox(hWnd, "Fail to read CPU Architecture", NULL, MB_OK);
		return NULL;
	}

}

bool Initializer::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	int const drive = _getdrive();
	struct _diskfree_t diskFree;
	_getdiskfree(drive, &diskFree);

	unsigned __int64 const neededCluster = diskSpaceNeeded / (diskFree.sectors_per_cluster * diskFree.bytes_per_sector);

	if (diskFree.avail_clusters < neededCluster)
	{
		MessageBox(hWnd, "CheckStorage Failure: Not enough physical storage.", NULL, MB_OK);
		return false;
	}

	std::cout << "CheckStorage Success: Enough physical storage." << std::endl;
	return true;
}

bool Initializer::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(hWnd, "Multiple Instances detected", NULL, MB_OK);
		return false;
	}
	return true;
}