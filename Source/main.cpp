#include<iostream>
#include<Windows.h>
#include<direct.h>

bool IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = OpenMutex(MUTEX_ALL_ACCESS, 0, gameTitle);

	if (!handle) // Mutex doesn't exist. This is the first instance so create the mutex.
	{
		handle = CreateMutex(NULL, TRUE, gameTitle);
	}
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);

		if (hWnd)
		{
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			//SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			//SetActiveWindow(hWnd);
			return false;
		}
	}
	//else// The mutex exists so this is the second instance so return.
	//{
	//	// Find the window of First Instance
	//	HWND hWnd = FindWindow(gameTitle, NULL);
	//	if (hWnd)
	//	{
	//		ShowWindow(hWnd, SW_SHOWNORMAL);
	//		SetForegroundWindow(hWnd);

	//		return false;
	//	}
	//}

	return true;


	//if (GetLastError() != ERROR_SUCCESS)
	//{
	//	HWND hWnd = FindWindow(gameTitle, NULL);

	//	if (hWnd) 
	//	{
	//		// An instance of your game is already running.
	//		ShowWindow(hWnd, SW_SHOWNORMAL);
	//		SetFocus(hWnd);
	//		SetForegroundWindow(hWnd);
	//		SetActiveWindow(hWnd);
	//		return false;
	//	}
	//}
	//return true;
}

int main()
{
	std::cout<< IsOnlyInstance("CoconutEngine-x64-Release") << std::endl;
	
	system("pause");
	return 0;
}