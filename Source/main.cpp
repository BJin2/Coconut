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
    {   // query the key:
        RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE) &dwMHz, &BufSize);
    }
    return dwMHz;
}

int main()
{
    std::cout << "CHECK MY CPU SPEED: " << ReadCpuSpeed() << std::endl;
	return 0;
}
