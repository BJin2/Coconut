#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/ScriptComponent.h"
#include "../Actors/Components/RendererComponent.h"


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
