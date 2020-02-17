#include "Scene.h"
#include "../Actors/Actor.h"

#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"
#include "../../Engines/InputCommand.hpp"
#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"

class RenderComponent;

void Scene::Initialize()
{
	Actor* first = new Actor();
	/*std::string name = "../../Lua/test.lua";
	test->AddComponent(name);*/
	first->AddComponent<RendererComponent>();
	first->AddComponent<Rigidbody>();
	Rigidbody* firstRigidbody = first->GetComponent<Rigidbody*>();
	firstRigidbody->SetCurrentVelocity(Vector2(3, 0));
	first->transform->SetPosition(50, 50);
	first->AddComponent<AudioComponent>();

	Actor* second = new Actor();
	second->AddComponent<RendererComponent>();
	second->AddComponent<Rigidbody>();
	Rigidbody* secondRigidbody = second->GetComponent<Rigidbody*>();
	secondRigidbody->SetCurrentVelocity(Vector2(-3, 0));
	second->transform->SetPosition(250, 50);

	actors.push_back(first);
	actors.push_back(second);


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

	actors[0]->GetComponent<AudioComponent>()->Play();
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
