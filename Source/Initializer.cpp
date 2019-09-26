#include "Initializer.h"

Initializer::Initializer()
{

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
		printf("CheckMomory Failure : Not enough physical memory.\n");
		return false;
	}

	//Check virtual memory
	if (status.ullAvailVirtual < virtualNeeded)
	{
		printf("CheckMomory Failure : Not enough virtual memory.\n");
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
		printf("CheckMemory Failure: Not enough contiguous memory.\n");
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
		printf("Fail to read CPU Architecture \n");
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
		std::cout << ("CheckStorage Failure: Not enough physical storage.") << std::endl;
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
		HWND hWnd = FindWindow(gameTitle, NULL);
		MessageBox(hWnd, "Multiple Instances detected", NULL, MB_OK);
		return false;
	}
	return true;
}