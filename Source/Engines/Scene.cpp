#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"

#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"
#include "GraphicEngine.hpp"

Scene::~Scene()
{
	for (auto actor : actors)
	{
		delete actor;
	}
}

void Scene::Initialize()
{
	std::string name = "../../Lua/test.lua";

	ExampleLoadedEventData data;
	data.example = "Scene Loaded";
	data.target = GraphicEngine::Instance()->GetGameScreen();
	EventManager::Instance()->RegisterEvent(data.type, &data);
}

void Scene::Start()
{
	for (auto actor : actors)
	{
		actor->VStart();
	}
}

void Scene::Update(float delta)
{
	for (auto actor : actors)
	{
		actor->VUpdate(delta);
	}
}

void Scene::DeleteAllActors()
{
	for (auto a : actors)
	{
		delete a;
	}
	actors.clear();
}

std::vector<Actor*> Scene::GetActor()
{
	return actors;
}

Actor* Scene::AddActor()
{
	Actor* actor = new Actor();
	actors.push_back(actor);
	return actor;
}

Actor* Scene::AddActor(std::string name)
{
	Actor* actor = new Actor(name);
	actors.push_back(actor);
	return actor;
}

Actor* Scene::Find(std::string name)
{
	for (auto actor : actors)
	{
		if (actor->name == name)
			return actor;
	}
	return nullptr;
}

std::vector<Actor*> Scene::FindAll(std::string name)
{
	std::vector<Actor*> result;
	for (auto actor : actors)
	{
		if (actor->name == name)
			result.push_back(actor);
	}
	return result;
}

void Scene::Destroy()
{
	for (auto actor = actors.begin(); actor != actors.end();)
	{
		if ((*actor)->destroyFlag)
		{
			delete (*actor);
			actor = actors.erase(actor);
		}
		else
		{
			actor++;
		}
	}
}

bool Scene::Destroy(std::string name)
{
	return Destroy(Find(name));
}

bool Scene::Destroy(Actor* _actor)
{
	for (auto actor : actors)
	{
		if (actor == _actor)
		{
			actor->destroyFlag = true;
			return true;
		}
	}

	return false;
}
