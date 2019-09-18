#include<iostream>

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
	return 0;
}
