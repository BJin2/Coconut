#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/Transform.h"

class RenderComponent;

void Scene::Initialize()
{
	Actor* test = new Actor();
	std::string name = "../../Lua/test.lua";
	test->AddComponent(name);
	test->AddComponent<RendererComponent>();
	actors.push_back(test);
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

Actor* Scene::AddActor()
{
	Actor* actor = new Actor();
	actors.push_back(actor);
}
