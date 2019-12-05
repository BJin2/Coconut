#include "Game.h"

Game* Game::GetInstance()
{
	return instance;
}

Game::Game()
{
	instance = this;
}

void Game::Start()
{
	for (auto actor : actors)
	{
		//actor.Start();
	}
}

void Game::Update(float delta)
{
	for (auto actor : actors)
	{
		//actor.Update(delta);
	}
}
