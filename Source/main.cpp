#include<iostream>
#include <window.h>
#include <direct.h>

bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{
    int const drive = _getdrive();
    struct _diskfree_t diskFree;
    _getDiskfree(drive, &diskFree);
    
    unsigned __int64 const neededCluster;
    neededCluster = diskSpaceNeeded / (diskFree.sectors_per_cluster * diskFree.bytes_per_sector);
    
    if(diskFree.avail_clusters < neededCluster)
    {
        GCC_ERROR("CheckStorage Failure: Not enough physical storage.");
        return false;
    }
    return true;
}

int main()
{
    CheckStorage(300);
	return 0;
}
