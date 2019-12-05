#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>  
#include <tchar.h>  
#include "Engines/InputInterface.h"
#include "Engines/Game.h"

extern "C"
{
#include "..//Libs/Lua535/include/lua.h"
#include "..//Libs/Lua535/include/lauxlib.h"
#include "..//Libs/Lua535/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "..//..//..//Libs/Lua535/liblua53.a")
#endif

bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

// Global variables  
Game* gGame;
HWND Game::hWnd = 0;

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
	_In_ int       nCmdShow)
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

	HWND hWnd = CreateWindow(
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 512,
		NULL,NULL,hInstance,NULL);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}
	
	gGame = new Game(hWnd);
	
	//need to create lua state to do anything with lua
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			gGame->Update(0.0f);
		}
	}

	delete gGame;
	lua_close(L);
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	IInput* input = new IInput();

	switch (message)
	{
	case WM_CHAR:
		input->VOnChar(wParam, hWnd);
		break;
	case WM_KEYDOWN:
		input->VOnKeyDown(wParam, hWnd);
		break;
	case WM_KEYUP:
		input->VOnKeyUp(wParam, hWnd);
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		input->VOnPointerMove(lParam, hWnd);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		input->VOnPointerButtonDown(lParam, hWnd);
		break;
	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		input->VOnPointerButtonUp(lParam, hWnd);
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