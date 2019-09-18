#include<iostream>
#include<Windows.h>
#include<direct.h>

bool IsOnlyInstance(LPCTSTR gameTitle) {

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
	std::cout<< IsOnlyInstance("CoconutEngine-x64-Release") << std::endl;
	
	system("pause");
	return 0;
}