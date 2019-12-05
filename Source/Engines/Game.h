#pragma once
#include"../Actors/Actor.h"

class Game
{
private:
	std::vector<Actor> actors;
	static Game* instance;

public:
	static Game* GetInstance();
	Game();
	void Start();
	void Update(float delta);
};