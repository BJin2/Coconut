#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/Rigidbody.h"

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

	Actor* second = new Actor();
	second->AddComponent<RendererComponent>();
	second->AddComponent<Rigidbody>();
	Rigidbody* secondRigidbody = second->GetComponent<Rigidbody*>();
	secondRigidbody->SetCurrentVelocity(Vector2(-3, 0));
	second->transform->SetPosition(250, 50);

	actors.push_back(first);
	actors.push_back(second);
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
	return actor;
}
