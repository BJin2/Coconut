#include<iostream>
#include<Windows.h>
#include<direct.h>

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

#include <Windows.h>
#include <direct.h>

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
	printf("CHECK MY CPU SPEED: %d GHz\n", ReadCpuSpeed());
	printf("CHECK MY CPU Architecture: %s\n", readCpuArchitecture());

	return 0;
}
