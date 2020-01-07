#include "Game.h"
#include "InputInterface.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/ScriptComponent.h"

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Coconut Engine");

// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Game::Game()
{
	Actor* test = new Actor();
	std::string name = "../../Lua/test.lua";
	test->AddComponent(name);
	actors.push_back(test);
}

void Game::Start()
{
	for (auto actor : actors)
	{
		actor->VStart();
	}
}

void Game::Update(float delta)
{
	// Main message loop:  
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		for (auto actor : actors)
		{
			actor->VUpdate(delta);
		}
	}
}

bool Game::CreateEngineWindow(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	hInst = hInstance;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
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


	HWND hWnd = CreateWindow(
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 512,
		NULL, NULL, hInst, NULL);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}
	Game::hWnd = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
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