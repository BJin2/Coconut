#include "Scene.h"
#include "../Actors/Actor.h"
#include "../Actors/Components/RendererComponent.h"
#include "../Actors/Components/AudioComponent.h"
#include "../Actors/Components/Transform.h"
#include "../Actors/Components/Rigidbody.h"
#include "../../Engines/InputCommand.hpp"

#include "Event/EventManager.h"
#include "Event/ExampleLoadedEvent.h"
#include "GraphicEngine.hpp"

class RenderComponent;

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

	Actor* player = AddActor("player");
	player->AddComponent<RendererComponent>();
	player->AddComponent<Rigidbody>();
	Rigidbody* cachedPlayerRigidBody = player->GetComponent<Rigidbody>();
	cachedPlayerRigidBody->SetRigidbodySettings(0.0f, 0.0f, false);//static
	cachedPlayerRigidBody->SetCurrentVelocity(Vector2(0, 0));
	player->transform->SetPosition(50, 50);

	Actor* bgm = AddActor("bgm");
	bgm->AddComponent<AudioComponent>();

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

	Find("bgm")->GetComponent<AudioComponent>()->Play();
	sf::Color colors[4] = { sf::Color::Red, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta};
	Find("player")->GetComponent<RendererComponent>()->SetColor(colors[0]);
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
