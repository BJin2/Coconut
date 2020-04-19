#pragma once
#include <vector>
#include "../Actors/Actor.h"

class Scene
{
private:
	std::vector<Actor*> actors;
	
public:
	~Scene();
	void Initialize();
	void Start();
	void Update(float delta);
	void DeleteAllActors();
	std::vector<Actor*> GetActor();
	Actor* AddActor();
};