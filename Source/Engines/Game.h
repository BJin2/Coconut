#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>
#include <tchar.h>
#include <chrono>
#include <ctime>
#include "Scene.h"
#include "Time.h"

class EventMapper;

class Game
{
public:
	static void Start();
	static void Initialize();
	static bool CreateEngineWindow(
		HINSTANCE hInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow);

	static HWND hWnd;
	static HWND SFMLView;
private:
	static void Update();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	enum GameState {Uninitialized, ShowingSplash, Playing, Exiting};
	static GameState gameState;
	static Scene* scene;
	static Time* time;
	static EventMapper* mapper;
};
