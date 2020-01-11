#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Initializer.h"
#include "InputInterface.h"
#include <SFML/Graphics.hpp>

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Coconut Engine");


void Game::Start()
{
	if (gameState == GameState::Uninitialized)
		return;

	CreateEngineWindow(nullptr, szTitle, SW_SHOW);
	gameState = GameState::Playing;
	scene->Start();
	Update();
}

void Game::Initialize()
{
	Initializer* initializer = new Initializer();
	if (initializer->CheckRequirements(szTitle, 1000, 1000, 1000))
	{
		gameState = GameState::ShowingSplash;
	}
	delete initializer;

	scene = new Scene();
	scene->Initialize();
}

void Game::Update()
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
		


		scene->Update(0.0f);
	}
}

bool Game::CreateEngineWindow(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
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


	HWND hWnd = CreateWindow(
		szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		512, 512,
		NULL, NULL, hInstance, NULL);

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

	HWND SFMLView1 = CreateWindow(
		szWindowClass, szTitle,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER,
		20, 250, 300, 200,
		hWnd, NULL, hInstance, NULL);

	if (!SFMLView1)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow(SFMLVIEW) failed!"),
			_T("Coconut Engine"),
			NULL);

		return 1;
	}

	Game::SFMLView = SFMLView1;
	sf::RenderWindow SFMLWindow(SFMLView1);
}

LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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