#pragma once
#include <windows.h>  
#include"../Actors/Actor.h"

class Game
{
private:
	std::vector<Actor*> actors;

public:
	Game(HWND _hWnd);
	void Start();
	void Update(float delta);
	static HWND hWnd;
};