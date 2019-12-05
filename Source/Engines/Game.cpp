#include "Game.h"

Game::Game(HWND _hWnd)
{
	Game::hWnd = _hWnd;
}

void Game::Start()
{
	for (auto actor : actors)
	{
		actor->Start();
	}
}

void Game::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->Update(delta);
	}
}

