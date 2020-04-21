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
	Actor* AddActor(std::string name);
	Actor* Find(std::string name);
	std::vector<Actor*> FindAll(std::string name);
	void Destroy();
	bool Destroy(std::string name);
	bool Destroy(Actor* actor);
};