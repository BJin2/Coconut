#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>  
#include <windowsx.h>
#include <stdlib.h>  
#include <tchar.h>  
#include"../Actors/Actor.h"

class Game
{
private:
	std::vector<Actor*> actors;

public:
	Game();
	void Start();
	void Update(float delta);
	
	bool CreateEngineWindow(
		_In_ HINSTANCE hInstance,
		_In_ HINSTANCE hPrevInstance,
		_In_ LPSTR     lpCmdLine,
		_In_ int       nCmdShow);
	static HWND hWnd;

private:
	HINSTANCE hInst;
	WNDCLASSEX wcex;
};