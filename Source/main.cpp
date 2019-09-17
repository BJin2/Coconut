#include<iostream>
#include<Windows.h>

#define DIV 1048576
bool CheckMemory(const DWORDLONG physicalNeeded, const DWORDLONG virtualNeeded);

int main()
{
	CheckMemory(100 * DIV, 100*DIV);
	return 0;
}

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