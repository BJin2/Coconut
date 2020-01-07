#pragma once
#include <vector>
#include "../Actors/Actor.h"

class Scene
{
private:
	std::vector<Actor*> actors;
	void Initialize();
public:
	void Start();
	void Update(float delta);
};