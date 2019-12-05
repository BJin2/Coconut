#include "Game.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/ScriptComponent.h"

Game::Game(HWND _hWnd)
{
	Game::hWnd = _hWnd;

	Actor* test = new Actor();
	std::string name = "C:/Users/bomja/Documents/Project/Assignment/Coconut/Source/Lua/test.lua";
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
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
	}
}

