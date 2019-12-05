#pragma once
#include <windows.h>  
#include"../Actors/Actor.h"

class Game
{
private:
	std::vector<Actor> actors;
	static Game* instance;
	HWND hWnd;

public:
	static Game* GetInstance();
	Game();
	void Start();
	void Update(float delta);
	HWND GetHWND();
};