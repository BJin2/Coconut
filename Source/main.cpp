#include<iostream>
#include<Windows.h>
#include<direct.h>

#define DIV 1048576
bool CheckMemory(const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);


	//Printing memory info
	printf("Total Physical Memory : %I64d MB\n", status.ullTotalPhys / DIV);
	printf("Available Physical Memory : %I64d MB\n", status.ullAvailPhys / DIV);
	printf("Total Virtual Memory : %I64d MB\n", status.ullTotalVirtual / DIV);
	printf("Available Virtual Memory : %I64d MB\n", status.ullAvailVirtual / DIV);

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

DWORD ReadCpuSpeed()
{
    DWORD BufSize = sizeof(DWORD);
    DWORD dwMHz =0;
    DWORD type = REG_DWORD;
    HKEY hKey;
    
    long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
    
    if(lError == ERROR_SUCCESS)
    {  
        RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE) &dwMHz, &BufSize);
    }
    return dwMHz;
}

char* readCpuArchitecture()
{
	char regVal[1024];
	//char *regVal = (char*)malloc(1024 * sizeof(char)); //If I use this one, sizeof(regVal) fixed at 8.
	HKEY hKey;
	DWORD size = sizeof(regVal);
	DWORD type = REG_SZ;
	//printf("SIZE: %d \n", size);

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS)
	{

		RegQueryValueEx(hKey, "ProcessorNameString", NULL, &type, (PBYTE)& regVal, &size);
		return regVal;
	}
	else
	{
		printf("Fail to read CPU Architecture \n");
		return NULL;
	}
	
}

bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
    int const drive = _getdrive();
    struct _diskfree_t diskFree;
	_getdiskfree(drive, &diskFree);
    
    unsigned __int64 const neededCluster = diskSpaceNeeded / (diskFree.sectors_per_cluster * diskFree.bytes_per_sector);
    
    if(diskFree.avail_clusters < neededCluster)
    {
		std::cout << ("CheckStorage Failure: Not enough physical storage.") << std::endl;
        return false;
    }

	std::cout << "CheckStorage Success: Enough physical storage." << std::endl;
    return true;
}

bool IsOnlyInstance(LPCTSTR gameTitle) 
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		//HWND hWnd = FindWindow(gameTitle, NULL);
		//if (hWnd != NULL) {
		//	// An instance of your game is already running.
		//	ShowWindow(hWnd, SW_SHOWNORMAL);
		//	SetFocus(hWnd);
		//	SetForegroundWindow(hWnd);
		//	SetActiveWindow(hWnd);
		//}
		return false;
	}
	return true;
}

int main()
{
	return 0;
}
