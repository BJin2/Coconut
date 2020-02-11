#pragma once
#include <vector>
#include "../Actors/Actor.h"

class Scene
{
private:
	std::vector<Actor*> actors;
	
public:
	void Initialize();
	void Start();
	void Update(double delta);
};