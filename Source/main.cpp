#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include <iostream>

// Global variables  

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Coconut Engine");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 512,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	int curMosePosX = GET_X_LPARAM(lParam);
	int curMosePosY = GET_Y_LPARAM(lParam);

	TCHAR charText[100] = _T("");
	_stprintf(charText, _T("WM_CHAR: %c\n"), (wchar_t)wParam);
	TCHAR keyDownText[100] = _T("");
	_stprintf(keyDownText, _T("WM_KEYDOWN: %c\n"), (wchar_t)wParam);
	TCHAR keyUpText[100] = _T("");
	_stprintf(keyUpText, _T("WM_KEYUP: %c\n"), (wchar_t)wParam);
	TCHAR mouseDownText[100] = _T("");
	_stprintf(mouseDownText, _T("LMouse Down x-pos: %d, LMouse Down y-pos: %d\n"), curMosePosX, curMosePosY);
	TCHAR mouseUpText[100] = _T("");
	_stprintf(mouseUpText, _T("LMouse UP x-pos: %d, LMouse Up y-pos: %d\n"), curMosePosX, curMosePosY);
	TCHAR mosueMoveText[100] = _T("");	
	_stprintf(mosueMoveText, _T("mouse x-pos: %d, mouse y-pos: %d\n"), curMosePosX, curMosePosY);

	switch (message)
	{
	case WM_CHAR:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 10, charText, sizeof(charText));
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 30, keyDownText, sizeof(keyDownText));
		break;
	case WM_KEYUP:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 50, keyUpText, sizeof(keyUpText));
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 70, mosueMoveText, sizeof(mosueMoveText));
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 90, mouseDownText, sizeof(mosueMoveText));
		break;
	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 110, mouseUpText, sizeof(mosueMoveText));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}