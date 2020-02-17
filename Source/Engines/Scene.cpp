#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/Transform.h"
#include "../../Engines/InputCommand.hpp"
#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"

class RenderComponent;

void Scene::Initialize()
{
	Actor* test = new Actor();
	std::string name = "../../Lua/test.lua";
	test->AddComponent(name);
	test->AddComponent<RendererComponent>();
	actors.push_back(test);

	printf("Exmaple event fires");
	ExampleLoadedEventData data;
	data.example = "Scene Loaded";
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

	//Input and translation testing
	if (InputCommand::GetKeyDown(InputCommand::Key::D))
	{
		actors[0]->transform->Translate(Vector2(1, 0), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::A))
	{
		actors[0]->transform->Translate(Vector2(-1, 0), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::W))
	{
		actors[0]->transform->Translate(Vector2(0, 1), 3 * delta);
	}
	if (InputCommand::GetKeyDown(InputCommand::Key::S))
	{
		actors[0]->transform->Translate(Vector2(0, -1), 3 * delta);
	}
}

Actor* Scene::AddActor()
{
	Actor* actor = new Actor();
	actors.push_back(actor);
	return actor;
}
