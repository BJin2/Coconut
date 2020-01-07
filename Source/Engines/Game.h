#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>  
#include <tchar.h>
#include "Scene.h"

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
private:
	static void Update();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	enum GameState {Uninitialized, ShowingSplash, Playing, Exiting};
	static GameState gameState;
	static Scene* scene;
};
