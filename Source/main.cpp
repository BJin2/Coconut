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

int main()
{
    CheckStorage(314572800);
	return 0;
}
